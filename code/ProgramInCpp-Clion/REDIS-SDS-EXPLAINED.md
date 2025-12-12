# Redis SDS (Simple Dynamic String) 详解

## 一、C 语言字符串的问题

在学习 Redis SDS 之前，先了解 C 语言字符串存在的问题：

### 1. 缓冲区溢出风险
```c
char buffer[10];
strcpy(buffer, "very long string");  // 危险！会溢出
```

### 2. 获取长度需要 O(n) 时间
```c
strlen(str);  // 必须遍历到 '\0' 才知道长度
```

### 3. 不能存储二进制数据
```c
// '\0' 作为字符串结束标志，无法存储包含 '\0' 的数据
char data[] = {'a', '\0', 'b'};  // strlen() 只能得到 1
```

### 4. 字符串拼接效率低
```c
strcat(s1, s2);  // 需要先 strlen(s1) 找到末尾，然后复制
```

### 5. 没有记录已分配大小
```c
char* str = malloc(100);  // 无法获知剩余可用空间
```

---

## 二、Redis SDS 数据结构

### 2.1 核心设计思想

Redis SDS 将**元数据（长度、容量）存储在字符串前面**，而指针指向实际的字符数组：

```
  内存布局：
  
  +--------+------+-----------+-----+-----------+
  | Header | Type | Flags     | ... | Buf       | <- sds 指针指向这里！
  +--------+------+-----------+-----+-----------+
  ^                                  ^
  |                                  |
  实际分配的起始地址                  返回给用户的指针（char*）
```

### 2.2 五种不同大小的头部结构

根据字符串长度，Redis 使用不同大小的头部以节省内存：

```c
// SDS 类型 5 (sdshdr5) - 最多 32 字节（很少使用）
struct __attribute__ ((__packed__)) sdshdr5 {
    unsigned char flags; // 低3位=类型，高5位=长度
    char buf[];          // 柔性数组
};

// SDS 类型 8 (sdshdr8) - 最多 255 字节
struct __attribute__ ((__packed__)) sdshdr8 {
    uint8_t len;         // 已使用长度
    uint8_t alloc;       // 已分配容量（不含头部和'\0'）
    unsigned char flags; // 低3位=类型
    char buf[];
};

// SDS 类型 16 (sdshdr16) - 最多 64KB
struct __attribute__ ((__packed__)) sdshdr16 {
    uint16_t len;
    uint16_t alloc;
    unsigned char flags;
    char buf[];
};

// SDS 类型 32 (sdshdr32) - 最多 4GB
struct __attribute__ ((__packed__)) sdshdr32 {
    uint32_t len;
    uint32_t alloc;
    unsigned char flags;
    char buf[];
};

// SDS 类型 64 (sdshdr64) - 理论上无限制
struct __attribute__ ((__packed__)) sdshdr64 {
    uint64_t len;
    uint64_t alloc;
    unsigned char flags;
    char buf[];
};
```

**关键点：**
- `__attribute__ ((__packed__))`: 禁止编译器填充对齐，节省内存
- `buf[]`: **柔性数组**（C99），不占用结构体大小
- `flags`: 低3位存储类型（0-4），高5位未使用

### 2.3 类型选择算法

```c
char sdsReqType(size_t string_size) {
    if (string_size < 1<<5)                                  // < 32
        return SDS_TYPE_5;
    if (string_size <= (1<<8) - sizeof(struct sdshdr8) - 1)  // <= 255-3-1
        return SDS_TYPE_8;
    if (string_size <= (1<<16) - sizeof(struct sdshdr16) - 1) // <= 65535-5-1
        return SDS_TYPE_16;
    if (string_size <= (1ll<<32) - sizeof(struct sdshdr32) - 1)
        return SDS_TYPE_32;
    return SDS_TYPE_64;
}
```

**设计巧妙之处：**
- 考虑了头部大小，确保 `alloc` 字段能完整表示分配的容量
- 自动选择最小能容纳的类型，节省内存

---

## 三、核心算法

### 3.1 获取长度 - O(1) 时间复杂度

```c
static inline size_t sdslen(const sds s) {
    switch (sdsType(s)) {  // 通过 flags 判断类型
        case SDS_TYPE_5: return SDS_TYPE_5_LEN(s);  // 从 flags 高5位读取
        case SDS_TYPE_8: return SDS_HDR(8,s)->len;
        case SDS_TYPE_16: return SDS_HDR(16,s)->len;
        case SDS_TYPE_32: return SDS_HDR(32,s)->len;
        case SDS_TYPE_64: return SDS_HDR(64,s)->len;
    }
    return 0;
}
```

**优势：** 直接读取 `len` 字段，O(1) 时间，而 C 的 `strlen()` 是 O(n)。

### 3.2 获取可用空间 - O(1)

```c
static inline size_t sdsavail(const sds s) {
    switch(sdsType(s)) {
        case SDS_TYPE_5: return 0;  // TYPE_5 不可修改
        case SDS_TYPE_8: {
            SDS_HDR_VAR(8,s);
            return sh->alloc - sh->len;  // 剩余 = 容量 - 已用
        }
        // ... 其他类型类似
    }
}
```

**优势：** 无需重新计算，立即知道是否需要扩容。

### 3.3 预分配策略（重要优化）

```c
#define SDS_MAX_PREALLOC (1024*1024)  // 1MB

sds sdsMakeRoomFor(sds s, size_t addlen) {
    // ... 判断是否需要扩容 ...
    
    // 计算新容量
    size_t newlen = len + addlen;
    
    if (newlen < SDS_MAX_PREALLOC)
        newlen *= 2;  // 小于 1MB：翻倍
    else
        newlen += SDS_MAX_PREALLOC;  // 大于 1MB：增加 1MB
    
    // ... 重新分配内存 ...
}
```

**策略：**
- **小字符串**（< 1MB）：**容量翻倍**，减少多次追加时的重新分配
- **大字符串**（≥ 1MB）：**每次增加 1MB**，避免过度浪费内存

**效果：** 连续追加字符时，摊销时间复杂度为 O(n)，而非朴素的 O(n²)。

### 3.4 二进制安全

SDS 通过 `len` 字段明确记录长度，而不依赖 `'\0'`：

```c
// 可以安全存储包含 '\0' 的数据
sds s = sdsnewlen("\x00\x01\x02", 3);
sdslen(s);  // 返回 3，而非 0
```

Redis 用此特性存储：
- 图片、视频等二进制数据
- 序列化的对象（包含空字节）

### 3.5 内存访问技巧

**如何从 `sds` 指针获取头部？**

```c
#define SDS_HDR(T,s) ((struct sdshdr##T *)((s)-(sizeof(struct sdshdr##T))))

// 示例：sdshdr8
// s 指向 buf
// s - sizeof(sdshdr8) = buf 的地址 - 头部大小 = 头部起始地址
```

**flags 字段的位置：**
- flags 总是在 buf 的**前一个字节**（`s[-1]`）
- 这样可以快速判断类型，无需知道完整的头部大小

```c
static inline unsigned char sdsType(const sds s) {
    return s[-1] & SDS_TYPE_MASK;  // flags 的低3位
}
```

---

## 四、与 C 字符串对比

| 特性 | C 字符串 (char*) | Redis SDS |
|------|-----------------|-----------|
| **获取长度** | O(n) - `strlen()` 遍历 | O(1) - 直接读取 `len` |
| **缓冲区溢出** | 易发生 | 自动扩容检查 |
| **二进制安全** | ❌ 不支持 (`'\0'` 结尾) | ✅ 支持（记录 `len`） |
| **追加效率** | O(n²)（多次 `strcat`） | 摊销 O(n)（预分配） |
| **内存占用** | 仅字符串 + `'\0'` | 字符串 + 头部（3-17字节） |
| **C 兼容性** | ✅ 原生支持 | ✅ `buf` 以 `'\0'` 结尾 |

---

## 五、实际应用场景

### 5.1 频繁追加

```c
// 构建 HTTP 响应
sds response = sdsempty();
response = sdscat(response, "HTTP/1.1 200 OK\r\n");
response = sdscat(response, "Content-Type: text/html\r\n");
response = sdscat(response, "\r\n<html>...");
// 预分配机制避免了多次内存重新分配
```

### 5.2 存储二进制数据

```c
// 存储序列化的对象
sds obj = sdsnewlen(binary_data, data_len);
// 即使 binary_data 包含 '\0'，也能正确存储
```

### 5.3 统计信息

```c
// 快速获取长度用于统计
size_t memory_used = sdslen(key) + sdslen(value);
```

---

## 六、设计精髓总结

1. **元数据前置**：头部在 `buf` 之前，`sds` 指针指向 `buf`，兼容 C 字符串
2. **类型分级**：根据长度选择最小头部，节省内存
3. **O(1) 操作**：长度、可用空间即时获取
4. **预分配策略**：翻倍/增量混合，平衡性能和内存
5. **二进制安全**：用 `len` 而非 `'\0'` 判断结束
6. **兼容性**：`buf` 仍以 `'\0'` 结尾，可用于 C 函数

---

## 七、代码示例

运行 [`4-c_cpp_string_problem.cpp`](file:///d:/work/mygithub/C-CppLearning/code/ProgramInCpp-Clion/chapter4/4-c_cpp_string_problem.cpp) 可以看到 C 字符串的问题演示。

**预期输出：**
```
=== 问题 1: 缓冲区溢出 ===
复制后的内容: This is a
说明：strncpy 只复制了 9 个字符，避免溢出

=== 问题 2: 获取长度需要 O(n) ===
字符串: Hello, World!
长度: 13 (strlen 需要遍历整个字符串)

=== 问题 3: 不能存储二进制数据 ===
实际数据长度: 12 字节
用 C 字符串函数: "Hello"
strlen: 5 (只到第一个 \0)

=== 问题 4: 字符串拼接效率低 ===
拼接后: Hello World
说明：每次拼接都可能需要重新分配内存

=== 问题 5: 没有记录已分配大小 ===
实际使用: 5 字节
已分配: 100 字节 (但 C 字符串无法获知)
剩余空间: 无法直接获取
```

---

## 八、参考资源

- [Redis SDS 源码 - sds.h](https://github.com/redis/redis/blob/unstable/src/sds.h)
- [Redis SDS 源码 - sds.c](https://github.com/redis/redis/blob/unstable/src/sds.c)
- [Redis 设计与实现 - SDS 章节](http://redisbook.com/)
