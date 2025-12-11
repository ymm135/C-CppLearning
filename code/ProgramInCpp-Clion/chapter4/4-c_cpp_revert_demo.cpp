// Chapter 4 - C++ 类型转换示例
// 包含: static_cast, const_cast, dynamic_cast, reinterpret_cast
#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

// 用于 dynamic_cast 示例的基类和派生类
class Base {
public:
    virtual ~Base() {}  // 必须有虚函数才能使用 dynamic_cast
    virtual void show() { std::cout << "Base class" << std::endl; }
};

class Derived : public Base {
public:
    void show() override { std::cout << "Derived class" << std::endl; }
    void derivedOnly() { std::cout << "Derived 特有方法" << std::endl; }
};

void setupConsole() {
    // 设置本地化环境，支持中文
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    
#ifdef _WIN32
    // 设置Windows控制台为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void demo_static_cast() {
    std::cout << "\n=== 1. static_cast 示例 ===" << std::endl;
    std::cout << "用途: 编译时类型转换，用于基本类型转换、类层次结构中的向上转换" << std::endl;
    
    // 示例1: 基本类型转换
    int i = 10;
    double d = static_cast<double>(i);
    std::cout << "int → double: " << i << " → " << d << std::endl;
    
    // 示例2: 浮点数转整数
    double pi = 3.14159;
    int int_pi = static_cast<int>(pi);
    std::cout << "double → int: " << pi << " → " << int_pi << " (截断小数)" << std::endl;
    
    // 示例3: 指针类型转换（向上转换）
    Derived* derived = new Derived();
    Base* base = static_cast<Base*>(derived);  // 派生类 → 基类（安全）
    std::cout << "派生类指针 → 基类指针: ";
    base->show();
    
    delete derived;
}

void demo_const_cast() {
    std::cout << "\n=== 2. const_cast 示例 ===" << std::endl;
    std::cout << "用途: 添加或移除 const/volatile 属性" << std::endl;
    
    // 示例1: 移除 const 属性
    const int const_value = 100;
    int* modifiable = const_cast<int*>(&const_value);
    std::cout << "原始 const 值: " << const_value << std::endl;
    std::cout << "通过 const_cast 获取的指针地址: " << modifiable << std::endl;
    // 注意: 修改原本是 const 的变量是未定义行为，这里仅演示语法
    
    // 示例2: 实际应用场景 - 调用不接受 const 的旧 API
    const char* const_str = "Hello";
    char* str = const_cast<char*>(const_str);
    std::cout << "移除 const 后的字符串: " << str << std::endl;
    // 警告: 不要修改字符串字面量！
}

void demo_dynamic_cast() {
    std::cout << "\n=== 3. dynamic_cast 示例 ===" << std::endl;
    std::cout << "用途: 运行时类型检查，安全的向下转换（基类 → 派生类）" << std::endl;
    
    // 示例1: 成功的向下转换
    Base* base_ptr = new Derived();  // 实际指向 Derived 对象
    Derived* derived_ptr = dynamic_cast<Derived*>(base_ptr);
    
    if (derived_ptr != nullptr) {
        std::cout << "✓ 向下转换成功，实际是 Derived 对象: ";
        derived_ptr->derivedOnly();
    } else {
        std::cout << "✗ 向下转换失败" << std::endl;
    }
    
    // 示例2: 失败的向下转换
    Base* pure_base = new Base();  // 实际是 Base 对象
    Derived* failed_cast = dynamic_cast<Derived*>(pure_base);
    
    if (failed_cast != nullptr) {
        std::cout << "✓ 转换成功" << std::endl;
    } else {
        std::cout << "✗ 向下转换失败，实际是 Base 对象（返回 nullptr）" << std::endl;
    }
    
    delete base_ptr;
    delete pure_base;
}

void demo_reinterpret_cast() {
    std::cout << "\n=== 4. reinterpret_cast 示例 ===" << std::endl;
    std::cout << "用途: 低级别的位模式重新解释，通常用于指针和整数之间的转换" << std::endl;
    
    // 示例1: 指针转换为整数
    int value = 42;
    int* ptr = &value;
    
    // 将指针转换为整数类型（获取地址值）
    uintptr_t addr = reinterpret_cast<uintptr_t>(ptr);
    std::cout << "指针地址: " << ptr << std::endl;
    std::cout << "转换为整数: 0x" << std::hex << addr << std::dec << std::endl;
    
    // 示例2: 整数转换回指针
    int* recovered_ptr = reinterpret_cast<int*>(addr);
    std::cout << "恢复的指针: " << recovered_ptr << std::endl;
    std::cout << "指针指向的值: " << *recovered_ptr << std::endl;
    
    // 示例3: 不相关类型的指针转换（危险！）
    double d = 3.14;
    int* int_ptr = reinterpret_cast<int*>(&d);
    std::cout << "将 double 的位模式解释为 int: " << *int_ptr << " (无意义的值)" << std::endl;
    
    std::cout << "\n⚠️  警告: reinterpret_cast 非常危险，只在必要时使用！" << std::endl;
}

int main()
{
    setupConsole();
    
    std::cout << "╔════════════════════════════════════════════╗" << std::endl;
    std::cout << "║   C++ 四种类型转换运算符完整示例           ║" << std::endl;
    std::cout << "╚════════════════════════════════════════════╝" << std::endl;
    
    demo_static_cast();
    demo_const_cast();
    demo_dynamic_cast();
    demo_reinterpret_cast();
    
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << "总结:" << std::endl;
    std::cout << "• static_cast      - 编译时转换，最常用，相对安全" << std::endl;
    std::cout << "• const_cast       - 修改 const/volatile 属性" << std::endl;
    std::cout << "• dynamic_cast     - 运行时类型检查，安全的多态转换" << std::endl;
    std::cout << "• reinterpret_cast - 低级别位重新解释，最危险" << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    
    return 0;
}