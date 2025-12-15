# Complex 类调试模式使用说明

## 启用调试模式

有两种方法启用详细的调试日志：

### 方法 1：修改 Complex.h（推荐）

编辑 `Complex.h` 文件，取消注释调试宏：

```cpp
// ========== 调试模式开关 ==========
#define COMPLEX_DEBUG  // <-- 取消注释这行
// ==================================
```

### 方法 2：在编译时定义

在 CMakeLists.txt 中添加编译定义：

```cmake
add_executable(chapter8_8-class-complex_main 
    8-class-complex_main.cpp Complex.cpp Complex.h)
    
# 添加调试定义
target_compile_definitions(chapter8_8-class-complex_main 
    PRIVATE COMPLEX_DEBUG)
```

---

## 调试输出示例

### 未启用调试模式

```
=== Complex Number Operations Demo ===

c1 (default): real value is  0  image value is 0
c2 (3, 4):    real value is  3  image value is 4
...
```

### 启用调试模式后

```
=== Complex Number Operations Demo ===
[DEBUG] 默认构造: Complex() -> (0, 0)
[DEBUG] 参数构造: Complex(3, 4) -> (3, 4)
[DEBUG] 拷贝构造: Complex(复制 (3, 4)) -> (3, 4)

c1 (default): real value is  0  image value is 0
[DEBUG] 析构函数: ~Complex() 释放对象 (0, 0)
c2 (3, 4):    real value is  3  image value is 4
[DEBUG] 析构函数: ~Complex() 释放对象 (3, 4)
c3 (copy c2): real value is  3  image value is 4
[DEBUG] 析构函数: ~Complex() 释放对象 (3, 4)

[DEBUG] 加法: (3, 4) + (3, 4) = (6, 8)
[DEBUG] 参数构造: Complex(6, 8) -> (6, 8)

c2 + c3 = real value is  6  image value is 8
[DEBUG] 析构函数: ~Complex() 释放对象 (6, 8)
[DEBUG] 参数构造: Complex(1, 1) -> (1, 1)
[DEBUG] 减法: (3, 4) - (1, 1) = (2, 3)
[DEBUG] 参数构造: Complex(2, 3) -> (2, 3)
[DEBUG] 析构函数: ~Complex() 释放对象 (1, 1)
...
```

---

## 调试日志说明

| 日志类型 | 触发时机 | 输出示例 |
|---------|---------|---------|
| **默认构造** | `Complex c1;` | `[DEBUG] 默认构造: Complex() -> (0, 0)` |
| **参数构造** | `Complex c2(3, 4);` | `[DEBUG] 参数构造: Complex(3, 4) -> (3, 4)` |
| **拷贝构造** | `Complex c3(c2);` | `[DEBUG] 拷贝构造: Complex(复制 (3, 4)) -> (3, 4)` |
| **赋值运算符** | `c1 = c2;` | `[DEBUG] 赋值运算符: (0, 0) = (3, 4)` |
| **析构函数** | 对象生命周期结束 | `[DEBUG] 析构函数: ~Complex() 释放对象 (3, 4)` |
| **加法** | `c1 + c2` | `[DEBUG] 加法: (3, 4) + (1, 2) = (4, 6)` |
| **复合加法** | `c1 += c2` | `[DEBUG] 复合加法: (3, 4) += (1, 2)`<br>`  结果: (4, 6)` |

---

## 学习价值

通过调试日志，您可以清楚地看到：

### 1. 对象生命周期
```
[DEBUG] 参数构造: Complex(3, 4) -> (3, 4)  // 创建
... 使用对象 ...
[DEBUG] 析构函数: ~Complex() 释放对象 (3, 4)  // 销毁
```

### 2. 临时对象的创建和销毁
```cpp
Complex c5 = c2 - Complex(1, 1);
```
会输出：
```
[DEBUG] 参数构造: Complex(1, 1) -> (1, 1)    // 创建临时对象
[DEBUG] 减法: (3, 4) - (1, 1) = (2, 3)      // 执行运算
[DEBUG] 参数构造: Complex(2, 3) -> (2, 3)    // 创建结果对象
[DEBUG] 析构函数: ~Complex() 释放对象 (1, 1)  // 销毁临时对象
```

### 3. 拷贝 vs 赋值
```cpp
Complex c3(c2);  // 拷贝构造
Complex c4;
c4 = c2;         // 赋值运算符
```

输出：
```
[DEBUG] 拷贝构造: Complex(复制 (3, 4)) -> (3, 4)
[DEBUG] 默认构造: Complex() -> (0, 0)
[DEBUG] 赋值运算符: (0, 0) = (3, 4)
```

### 4. 自赋值检测
```cpp
c1 = c1;  // 自己赋值给自己
```
输出：
```
[DEBUG] 赋值运算符: 自赋值检测，跳过
```

---

## 实践建议

### 初学者
1. ✅ **启用调试模式**学习对象生命周期
2. ✅ 观察哪些操作会创建临时对象
3. ✅ 理解构造和析构的调用顺序

### 进阶练习
1. 修改代码，观察不同的对象创建方式
2. 对比拷贝构造和赋值运算符的区别
3. 分析复杂表达式的对象创建过程

### 性能分析
1. 统计临时对象的数量
2. 优化代码减少不必要的拷贝
3. 使用移动语义（C++11+）替代拷贝

---

## 关闭调试模式

完成学习后，记得关闭调试模式以提升性能：

```cpp
// 注释掉或删除这行
// #define COMPLEX_DEBUG
```

---

## 扩展建议

可以添加更多调试信息：

```cpp
// 在 Complex.h 添加
#ifdef COMPLEX_DEBUG
    #define DEBUG_LOG(msg) cout << "[DEBUG] " << msg << endl
    #define DEBUG_COUNT(msg) static int count = 0; cout << "[COUNT #" << ++count << "] " << msg << endl
#else
    #define DEBUG_LOG(msg)
    #define DEBUG_COUNT(msg)
#endif
```

然后在关键位置添加：
```cpp
DEBUG_COUNT("对象创建");  // 统计创建了多少个对象
```

---

**总结**：调试模式是学习 C++ 对象生命周期和内存管理的绝佳工具！
