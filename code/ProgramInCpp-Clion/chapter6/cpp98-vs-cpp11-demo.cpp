#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>

using namespace std;

// ========================================
// C++98 vs C++11+ 对比示例
// ========================================

// 1. auto 类型推导
void demo_auto() {
    cout << "\n=== Demo 1: auto 类型推导 ===" << endl;
    
    // C++98: 冗长的类型声明
    vector<int> vec = {1, 2, 3, 4, 5};
    vector<int>::iterator it98 = vec.begin();
    
    // C++11+: auto 自动推导
    auto it11 = vec.begin();
    
    // 复杂类型更明显
    map<string, vector<int>> complex_map;
    // C++98: 写起来痛苦
    // map<string, vector<int>>::iterator mit98 = complex_map.begin();
    // C++11+: 简洁
    auto mit11 = complex_map.begin();
    
    cout << "auto makes code cleaner!" << endl;
}

// 2. 智能指针 vs 裸指针
void demo_smart_pointers() {
    cout << "\n=== Demo 2: Smart Pointers ===" << endl;
    
    // C++98: 手动管理内存
    {
        int* p98 = new int(42);
        cout << "C++98 raw pointer: " << *p98 << endl;
        delete p98;  // 容易忘记！
    }
    
    // C++11: unique_ptr (独占所有权)
    {
        auto p11 = make_unique<int>(42);
        cout << "C++11 unique_ptr: " << *p11 << endl;
        // 自动释放，无需 delete
    }
    
    // shared_ptr (共享所有权)
    {
        auto p1 = make_shared<int>(100);
        auto p2 = p1;  // 引用计数 = 2
        cout << "shared_ptr value: " << *p1 << endl;
        cout << "Reference count: " << p1.use_count() << endl;
    }
}

// 3. Lambda vs 函数对象
void demo_lambda() {
    cout << "\n=== Demo 3: Lambda Expression ===" << endl;
    
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // C++98: 需要定义函数对象
    struct Greater {
        bool operator()(int a, int b) const { return a > b; }
    };
    vector<int> vec98 = numbers;
    sort(vec98.begin(), vec98.end(), Greater());
    
    // C++11: Lambda 表达式
    vector<int> vec11 = numbers;
    sort(vec11.begin(), vec11.end(), [](int a, int b) {
        return a > b;
    });
    
    cout << "Sorted (descending): ";
    for (auto n : vec11) cout << n << " ";
    cout << endl;
    
    // Lambda 捕获变量
    int threshold = 5;
    auto count = count_if(numbers.begin(), numbers.end(), 
        [threshold](int n) { return n > threshold; });
    cout << "Numbers > " << threshold << ": " << count << endl;
}

// 4. Range-based for
void demo_range_for() {
    cout << "\n=== Demo 4: Range-based For Loop ===" << endl;
    
    vector<string> langs = {"C", "C++", "Python", "Java"};
    
    // C++98: 使用迭代器
    cout << "C++98 style: ";
    for (vector<string>::iterator it = langs.begin(); 
         it != langs.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // C++11: Range-based for
    cout << "C++11 style: ";
    for (const auto& lang : langs) {
        cout << lang << " ";
    }
    cout << endl;
}

// 5. nullptr vs NULL
void demo_nullptr() {
    cout << "\n=== Demo 5: nullptr ===" << endl;
    
    // C++98: NULL 实际上是 0
    int* p98 = NULL;
    
    // C++11: nullptr 类型安全
    int* p11 = nullptr;
    
    if (p11 == nullptr) {
        cout << "Pointer is null (type-safe!)" << endl;
    }
}

// 6. 统一初始化
void demo_uniform_init() {
    cout << "\n=== Demo 6: Uniform Initialization ===" << endl;
    
    // C++98: 多种初始化方式
    int a98 = 10;
    int b98(20);
    
    // C++11: 统一的大括号初始化
    int a11{10};
    vector<int> vec{1, 2, 3, 4, 5};
    map<string, int> m{{"one", 1}, {"two", 2}};
    
    cout << "Vector: ";
    for (auto n : vec) cout << n << " ";
    cout << endl;
    
    // 防止窄化
    // int x{3.14};  // 编译错误！
}

// 7. 移动语义示例
class BigData {
    int* data;
    size_t size;
public:
    BigData(size_t s) : size(s) {
        data = new int[size];
        cout << "Constructed BigData[" << size << "]" << endl;
    }
    
    ~BigData() {
        delete[] data;
        cout << "Destroyed BigData" << endl;
    }
    
    // C++11: 移动构造函数
    BigData(BigData&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "Moved BigData (no copy!)" << endl;
    }
    
    // 禁止拷贝
    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;
};

void demo_move_semantics() {
    cout << "\n=== Demo 7: Move Semantics ===" << endl;
    
    BigData data1(1000000);
    BigData data2 = move(data1);  // 移动，不拷贝
    // data1 现在为空
}

int main() {
    cout << "======================================" << endl;
    cout << "  C++98 vs C++11+ Feature Comparison" << endl;
    cout << "======================================" << endl;
    
    demo_auto();
    demo_smart_pointers();
    demo_lambda();
    demo_range_for();
    demo_nullptr();
    demo_uniform_init();
    demo_move_semantics();
    
    cout << "\n======================================" << endl;
    cout << "Modern C++ makes code safer and cleaner!" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
