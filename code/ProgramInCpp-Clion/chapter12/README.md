# C++ 底层实现学习 - 快速开始

##  目标

通过实际代码+调试+汇编分析，深入理解C++底层机制。

---

## 📁 文件说明

| 文件 | 内容 |
|------|------|
| `cpp-internals.cpp` | 综合demo（9个部分） |
| `CPP底层分析指南.md` | 工具使用指南 |
| `README.md` | 本文件 |

---

## 🚀 快速开始

### 步骤1：编译运行

```bash
cd d:\work\mygithub\C-CppLearning\code\ProgramInCpp-Clion\chapter12

# 编译（关闭优化）
g++ -O0 -g -std=c++17 cpp-internals.cpp -o cpp-internals

# 运行
.\cpp-internals
```

### 步骤2：查看汇编

```bash
# 生成汇编文件
g++ -S -O0 -fverbose-asm -std=c++17 cpp-internals.cpp -o cpp-internals.s

# 查看汇编
notepad cpp-internals.s
```

### 步骤3：GDB调试

```bash
# 启动GDB
gdb .\cpp-internals

# 设置断点
(gdb) break part4_vtable

# 运行
(gdb) run

# 查看vtable
(gdb) print c
(gdb) x/16gx &c
```

---

## 📚 学习内容概览

### Part 1: 基本类型内存布局
- 各类型大小
- 内存地址
- 指针大小

**关键点：**
- 64位系统指针为8字节
- 类型大小是编译时确定的

### Part 2: 结构体内存对齐
- 对齐原则
- padding填充
- `#pragma pack`

**关键点：**
```
struct NoAlign {
    char c;    // 偏移0，占1字节
    [3字节填充]
    int i;     // 偏移4，占4字节
    char c2;   // 偏移8，占1字节
    [3字节填充]
};  // 总共12字节
```

### Part 3: 类的内存布局
- 空类占1字节
- 数据成员按声明顺序排列
- 有虚函数时增加vptr

**关键点：**
```
WithVirtual对象布局：
+-------------------+
| vptr (8字节)      |
+-------------------+
| data (4字节)      |
+-------------------+
| [4字节填充]       |
+-------------------+
总计：16字节
```

### Part 4: 虚函数表（vtable）
- vptr指向vtable
- 虚函数通过vtable间接调用
- 派生类覆盖vtable中的函数指针

**多态原理：**
```cpp
Base* ptr = &child;
ptr->vfunc1();  

// 汇编实现：
// mov rax, [ptr]        ; 取vptr
// mov rax, [rax]        ; 取vtable第一项
// call rax              ; 调用Child::vfunc1
```

### Part 5: 函数调用与栈帧
- 参数传递（寄存器 vs 栈）
- 栈帧设置（push rbp, mov rbp, rsp）
- 栈生长方向

**x64调用约定（Windows）：**
1. RCX - 第1个参数
2. RDX - 第2个参数
3. R8  - 第3个参数
4. R9  - 第4个参数

### Part 6: Lambda表达式内存布局
- 无捕获：空对象（1字节）
- 值捕获：成员变量（捕获变量大小）
- 引用捕获：指针（8字节/引用）

**本质：**
```cpp
auto lambda = [x, y]() { ... };

// 等价于：
class __lambda_1 {
    int x, y;
public:
    void operator()() const { ... }
};
```

### Part 7: 模板实例化
- 编译器为每个类型生成代码
- 模板在链接时解析

**代码膨胀：**
```cpp
TemplateClass<int>    // 生成代码1
TemplateClass<double> // 生成代码2
TemplateClass<char>   // 生成代码3
```

### Part 8: 内存区域分布
- `.data段` - 全局/静态变量
- `.rodata段` - 常量
- `stack` - 栈
- `heap` - 堆

### Part 9: 类型转换
- `dynamic_cast` - 需要RTTI
- `typeid` - 需要虚函数

---

## 🔍 调试练习

### 练习1：查看vtable

```gdb
(gdb) break part4_vtable
(gdb) run
(gdb) print c
(gdb) x/16gx &c              # 查看对象内存
(gdb) set $vptr = *(void**)&c
(gdb) x/10gx $vptr           # 查看vtable
```

**任务：** 手动找出vtable中每个虚函数的地址

### 练习2：Lambda捕获

```gdb
(gdb) break part6_lambda_internals
(gdb) run
(gdb) print lambda2
(gdb) print sizeof(lambda2)  # 应该是8字节（两个int）
(gdb) x/8bx &lambda2         # 查看捕获的x和y
```

### 练习3：栈帧分析

```gdb
(gdb) break cdecl_func
(gdb) run
(gdb) info frame
(gdb) info registers
(gdb) disassemble
```

**观察：**
- 函数序言（prologue）
- 参数位置
- 局部变量分配

---

## 🎯 学习路径

### 阶段1：观察（1天）
运行demo，查看输出，理解基本概念

### 阶段2：调试（2-3天）
使用GDB，查看内存，验证理论

### 阶段3：汇编（3-5天）
生成汇编，理解指令，分析实现

### 阶段4：实战（持续）
自己写代码，查看底层实现，加深理解

---

## 📖 推荐阅读顺序

1. 运行demo，查看输出
2. 阅读 `CPP底层分析指南.md`
3. 使用GDB调试Part 4（vtable）
4. 生成汇编，研究函数调用
5. 自己修改代码，观察变化

---

## ⚙️ 工具清单

**必备：**
- GCC/MinGW - 编译器
- GDB - 调试器
- 文本编辑器 - 查看汇编

**可选：**
- Compiler Explorer - 在线汇编查看
- Visual Studio - MSVC工具链
- Valgrind - 内存分析（Linux）

---

## 🎓 学习成果

完成本章学习后，你将掌握：

✅ 类的内存布局  
✅ 虚函数表原理  
✅ Lambda的本质  
✅ 函数调用机制  
✅ 模板实例化  
✅ 内存对齐规则  

**最重要的：** 能够通过调试和汇编，自己分析任何C++特性的底层实现！

---

## 💡 提示

1. **关闭优化** - 编译时使用`-O0`
2. **加调试信息** - 使用`-g`
3. **小步调试** - 每次只关注一个函数
4. **对比输出** - 修改代码看变化
5. **查文档** - 不懂的指令查汇编手册

---

## 🔗 相关资源

- [Intel x86-64手册](https://www.intel.com/content/www/us/en/developer/articles/technical/intel-sdm.html)
- [GDB官方文档](https://sourceware.org/gdb/documentation/)
- [Compiler Explorer](https://godbolt.org/)
- [C++ Internals (书籍)](https://www.amazon.com/Inside-Object-Model-Stanley-Lippman/dp/0201834545)

---

**开始探索C++的底层世界吧！ 🚀**
