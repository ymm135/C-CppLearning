#include <iostream>
#include <cstddef>  // for offsetof
#include <typeinfo> // for typeid

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ============================================
// C++ 底层实现深度学习 - 完整Demo
// ============================================

// ==========================================
// 第一部分：基本类型内存布局
// ==========================================

void part1_basic_types() {
    cout << "\n========== 第一部分：基本类型内存布局 ==========" << endl;
    
    // 1. 基本类型大小
    cout << "\n--- 基本类型大小 ---" << endl;
    cout << "bool:        " << sizeof(bool) << " 字节" << endl;
    cout << "char:        " << sizeof(char) << " 字节" << endl;
    cout << "short:       " << sizeof(short) << " 字节" << endl;
    cout << "int:         " << sizeof(int) << " 字节" << endl;
    cout << "long:        " << sizeof(long) << " 字节" << endl;
    cout << "long long:   " << sizeof(long long) << " 字节" << endl;
    cout << "float:       " << sizeof(float) << " 字节" << endl;
    cout << "double:      " << sizeof(double) << " 字节" << endl;
    cout << "指针:        " << sizeof(void*) << " 字节" << endl;
    
    // 2. 内存地址
    int a = 10;
    int b = 20;
    cout << "\n--- 变量内存地址 ---" << endl;
    cout << "a的地址: " << &a << " 值: " << a << endl;
    cout << "b的地址: " << &b << " 值: " << b << endl;
    cout << "地址差: " << (char*)&b - (char*)&a << " 字节" << endl;
}

// ==========================================
// 第二部分：结构体内存对齐
// ==========================================

// 无对齐
struct NoAlign {
    char c;    // 1字节
    int i;     // 4字节
    char c2;   // 1字节
};

// 手动对齐
struct ManualAlign {
    char c;    // 1字节
    char pad[3]; // 填充3字节
    int i;     // 4字节
    char c2;   // 1字节
    char pad2[3]; // 填充3字节
};

#pragma pack(push, 1)  // 取消对齐
struct Packed {
    char c;
    int i;
    char c2;
};
#pragma pack(pop)

void part2_struct_alignment() {
    cout << "\n========== 第二部分：结构体内存对齐 ==========" << endl;
    
    cout << "NoAlign 大小: " << sizeof(NoAlign) << " 字节" << endl;
    cout << "Packed 大小: " << sizeof(Packed) << " 字节" << endl;
    
    NoAlign na;
    cout << "\nNoAlign 成员偏移:" << endl;
    cout << "c 偏移:  " << offsetof(NoAlign, c) << endl;
    cout << "i 偏移:  " << offsetof(NoAlign, i) << endl;
    cout << "c2 偏移: " << offsetof(NoAlign, c2) << endl;
    
    cout << "\nNoAlign 成员地址:" << endl;
    cout << "结构体地址: " << &na << endl;
    cout << "c 地址:  " << (void*)&na.c << endl;
    cout << "i 地址:  " << (void*)&na.i << endl;
    cout << "c2 地址: " << (void*)&na.c2 << endl;
}

// ==========================================
// 第三部分：类的内存布局
// ==========================================

// 空类
class Empty {
    // 空类大小为1（占位符）
};

// 只有数据成员的类
class DataOnly {
    int a;
    double b;
    char c;
public:
    DataOnly(int x, double y, char z) : a(x), b(y), c(z) {}
    void print_addresses() {
        cout << "对象地址: " << this << endl;
        cout << "a地址: " << &a << " 偏移: " << (char*)&a - (char*)this << endl;
        cout << "b地址: " << &b << " 偏移: " << (char*)&b - (char*)this << endl;
        cout << "c地址: " << &c << " 偏移: " << (char*)&c - (char*)this << endl;
    }

    // 新增的虚函数（只用于测试）
    virtual void vf() {
        cout << "virtual function" << endl;
    }
};

// 带虚函数的类
class WithVirtual {
    int data;
public:
    WithVirtual() : data(42) {}
    virtual void func1() { cout << "WithVirtual::func1" << endl; }
    virtual void func2() { cout << "WithVirtual::func2" << endl; }
    
    void print_layout() {
        cout << "对象大小: " << sizeof(*this) << " 字节" << endl;
        cout << "对象地址: " << this << endl;
        cout << "data地址: " << &data << endl;
        cout << "this指针前8字节(vptr): " << *(void**)this << endl;
    }
};

class Derived : public WithVirtual {
    int derived_data;
public:
    Derived() : derived_data(100) {}
    void func1() override { cout << "Derived::func1" << endl; }
    virtual void func3() { cout << "Derived::func3" << endl; }
};

void part3_class_layout() {
    cout << "\n========== 第三部分：类的内存布局 ==========" << endl;
    
    cout << "\n--- 空类 ---" << endl;
    cout << "Empty 大小: " << sizeof(Empty) << " 字节" << endl;
    
    cout << "\n--- 只有数据成员 ---" << endl;
    cout << "DataOnly 大小: " << sizeof(DataOnly) << " 字节" << endl;
    DataOnly obj(10, 3.14, 'A');
    obj.print_addresses();
    DataOnly* pDO = &obj;
    pDO->vf();
    
    cout << "\n--- 带虚函数的类 ---" << endl;
    cout << "WithVirtual 大小: " << sizeof(WithVirtual) << " 字节" << endl;
    WithVirtual vobj;
    vobj.print_layout();
    
    cout << "\n--- 派生类 ---" << endl;
    cout << "Derived 大小: " << sizeof(Derived) << " 字节" << endl;
}

// ==========================================
// 第四部分：虚函数表 (vtable)
// ==========================================

class Base {
public:
    int base_data = 1;
    virtual void vfunc1() { cout << "Base::vfunc1" << endl; }
    virtual void vfunc2() { cout << "Base::vfunc2" << endl; }
    void normal_func() { cout << "Base::normal_func (非虚)" << endl; }
};

class Child : public Base {
public:
    int child_data = 2;
    void vfunc1() override { cout << "Child::vfunc1 (重写)" << endl; }
    virtual void vfunc3() { cout << "Child::vfunc3 (新虚函数)" << endl; }
};

void part4_vtable() {
    cout << "\n========== 第四部分：虚函数表 ==========" << endl;
    
    Base b;
    Child c;
    
    cout << "\n--- 对象大小 ---" << endl;
    cout << "Base 大小: " << sizeof(Base) << " 字节 (vptr + base_data)" << endl;
    cout << "Child 大小: " << sizeof(Child) << " 字节 (vptr + base_data + child_data)" << endl;
    
    cout << "\n--- 内存布局 ---" << endl;
    cout << "Base 对象地址: " << &b << endl;
    cout << "Base vptr地址: " << &b << endl;
    cout << "Base vptr值(vtable地址): " << *(void**)&b << endl;
    
    cout << "\nChild 对象地址: " << &c << endl;
    cout << "Child vptr值(vtable地址): " << *(void**)&c << endl;
    
    cout << "\n--- 多态调用 ---" << endl;
    Base* ptr = &c;  // 基类指针指向派生类对象
    ptr->vfunc1();   // 调用 Child::vfunc1 (通过vtable)
    ptr->vfunc2();   // 调用 Base::vfunc2
    ptr->normal_func(); // 静态绑定，调用 Base::normal_func
}

// ==========================================
// 第五部分：函数调用约定和栈帧
// ==========================================

int __cdecl cdecl_func(int a, int b, int c) {
    cout << "cdecl调用，参数: " << a << ", " << b << ", " << c << endl;
    cout << "局部变量地址: a=" << &a << " b=" << &b << " c=" << &c << endl;
    return a + b + c;
}

void print_stack_info() {
    int stack_var1;
    int stack_var2;
    int stack_var3;
    
    cout << "\n堆栈生长方向检测:" << endl;
    cout << "stack_var1: " << &stack_var1 << endl;
    cout << "stack_var2: " << &stack_var2 << endl;
    cout << "stack_var3: " << &stack_var3 << endl;
    
    if ((char*)&stack_var2 < (char*)&stack_var1) {
        cout << "栈向下生长 (高地址→低地址)" << endl;
    } else {
        cout << "栈向上生长 (低地址→高地址)" << endl;
    }
}

void part5_function_calls() {
    cout << "\n========== 第五部分：函数调用与栈帧 ==========" << endl;
    
    int result = cdecl_func(10, 20, 30);
    cout << "返回值: " << result << endl;
    
    print_stack_info();
}

// ==========================================
// 第六部分：Lambda表达式内存布局
// ==========================================

void part6_lambda_internals() {
    cout << "\n========== 第六部分：Lambda表达式内存布局 ==========" << endl;
    
    // 1. 无捕获Lambda
    auto lambda1 = []() { cout << "无捕获Lambda" << endl; };
    cout << "无捕获Lambda大小: " << sizeof(lambda1) << " 字节" << endl;
    
    // 2. 值捕获Lambda
    int x = 10;
    int y = 20;
    auto lambda2 = [x, y]() { cout << "捕获: " << x << ", " << y << endl; };
    cout << "值捕获Lambda大小: " << sizeof(lambda2) << " 字节" << endl;
    cout << "Lambda对象地址: " << &lambda2 << endl;
    
    // 3. 引用捕获Lambda
    auto lambda3 = [&x, &y]() {
        x++; y++;
    };
    cout << "引用捕获Lambda大小: " << sizeof(lambda3) << " 字节" << endl;
    lambda3();
    
    // 4. 泛型Lambda (C++14)
    auto lambda4 = [](auto a, auto b) { return a + b; };
    cout << "泛型Lambda大小: " << sizeof(lambda4) << " 字节" << endl;
    
    // 验证lambda就是函数对象
    struct EquivalentFunctor {
        int captured_x;
        int captured_y;
        void operator()() const {
            cout << "等价函数对象: " << captured_x << ", " << captured_y << endl;
        }
    };
    
    EquivalentFunctor functor{x, y};
    cout << "\n等价函数对象大小: " << sizeof(functor) << " 字节" << endl;
    cout << "证明：Lambda本质是编译器生成的函数对象！" << endl;
}

// ==========================================
// 第七部分：模板实例化
// ==========================================

template<typename T>
class TemplateClass {
    T data;
public:
    TemplateClass(T val) : data(val) {}
    void print() {
        cout << "TemplateClass<" << typeid(T).name() << "> 大小: " 
             << sizeof(*this) << " 字节, 值: " << data << endl;
    }
};

template<typename T>
T add(T a, T b) {
    return a + b;
}

void part7_templates() {
    cout << "\n========== 第七部分：模板实例化 ==========" << endl;
    
    cout << "\n--- 类模板实例化 ---" << endl;
    TemplateClass<int> t1(42);
    t1.print();
    
    TemplateClass<double> t2(3.14);
    t2.print();
    
    TemplateClass<char> t3('A');
    t3.print();
    
    cout << "\n--- 函数模板实例化 ---" << endl;
    cout << "add<int>(10, 20) = " << add(10, 20) << endl;
    cout << "add<double>(1.5, 2.5) = " << add(1.5, 2.5) << endl;
    
    cout << "\n编译器会为每个类型生成独立的代码！" << endl;
}

// ==========================================
// 第八部分：内存区域
// ==========================================

int global_var = 100;        // 全局变量（.data段）
const int global_const = 200; // 常量（.rodata段）
static int static_var = 300; // 静态变量（.data段）

void part8_memory_segments() {
    cout << "\n========== 第八部分：内存区域分布 ==========" << endl;
    
    int stack_var = 10;      // 栈
    static int func_static = 20; // 静态变量
    int* heap_var = new int(30); // 堆
    
    cout << "\n--- 各段地址 ---" << endl;
    cout << "全局变量:   " << &global_var << " (.data段)" << endl;
    cout << "全局常量:   " << &global_const << " (.rodata段)" << endl;
    cout << "静态变量:   " << &static_var << " (.data段)" << endl;
    cout << "静态局部:   " << &func_static << " (.data段)" << endl;
    cout << "栈变量:     " << &stack_var << " (stack)" << endl;
    cout << "堆变量:     " << heap_var << " (heap)" << endl;
    cout << "字符串常量: " << (void*)"Hello" << " (.rodata段)" << endl;
    
    delete heap_var;
}

// ==========================================
// 第九部分：类型转换
// ==========================================

void part9_type_casting() {
    cout << "\n========== 第九部分：类型转换 ==========" << endl;
    
    Base base_obj;
    Child child_obj;
    
    cout << "\n--- dynamic_cast (RTTI) ---" << endl;
    Base* base_ptr = &child_obj;
    Child* child_ptr = dynamic_cast<Child*>(base_ptr);
    if (child_ptr) {
        cout << "dynamic_cast 成功！base_ptr实际指向Child对象" << endl;
    }
    
    cout << "\n--- typeid (RTTI) ---" << endl;
    cout << "base_ptr类型: " << typeid(*base_ptr).name() << endl;
    cout << "需要虚函数才能获取动态类型！" << endl;
}

// ==========================================
// 主函数
// ==========================================

int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif
    
    cout << "============================================" << endl;
    cout << "  C++ 底层实现深度学习 - 完整Demo" << endl;
    cout << "============================================" << endl;
    cout << "\n编译选项：" << endl;
    cout << "  查看汇编: g++ -S -O0 cpp-internals.cpp" << endl;
    cout << "  查看符号: nm cpp-internals.o" << endl;
    cout << "  GDB调试:  gdb ./cpp-internals" << endl;
    cout << "============================================" << endl;
    
    part1_basic_types();
    part2_struct_alignment();
    part3_class_layout();
    part4_vtable();
    part5_function_calls();
    part6_lambda_internals();
    part7_templates();
    part8_memory_segments();
    part9_type_casting();
    
    cout << "\n============================================" << endl;
    cout << "  完成！请使用调试工具深入分析" << endl;
    cout << "============================================" << endl;
    
    return 0;
}
