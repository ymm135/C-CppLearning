#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <optional>
#include <variant>

using namespace std;

// ========================================
// 现代 C++ 最佳实践
// ========================================

// 1. 优先使用智能指针，避免裸指针
class Resource {
    string name;
public:
    explicit Resource(const string& n) : name(n) {
        cout << "Resource '" << name << "' created" << endl;
    }
    ~Resource() {
        cout << "Resource '" << name << "' destroyed" << endl;
    }
    void use() const { cout << "Using " << name << endl; }
};

void best_practice_smart_pointers() {
    cout << "\n=== Best Practice 1: Smart Pointers ===" << endl;
    
    // ❌ 不推荐
    // Resource* r = new Resource("old");
    // r->use();
    // delete r;  // 容易忘记
    
    // ✅ 推荐: unique_ptr (独占所有权)
    auto r1 = make_unique<Resource>("modern1");
    r1->use();
    
    // ✅ 推荐: shared_ptr (共享所有权)
    auto r2 = make_shared<Resource>("modern2");
    auto r3 = r2;  // 共享
    cout << "Shared count: " << r2.use_count() << endl;
}

// 2. 使用 auto 减少冗余，但保持可读性
void best_practice_auto() {
    cout << "\n=== Best Practice 2: auto Usage ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // ✅ 好的使用
    auto it = numbers.begin();  // 明显是迭代器
    auto sum = 0;               // 明显是 int
    
    // ⚠️ 谨慎使用（类型不明显）
    auto x = some_complex_function();  // 不知道返回什么类型
    
    // ✅ 必须使用的场景
    auto lambda = [](int x) { return x * 2; };
}

// 3. Lambda 表达式最佳实践
void best_practice_lambda() {
    cout << "\n=== Best Practice 3: Lambda ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // ✅ 简单操作用 Lambda
    auto evens = vector<int>();
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
        [](int n) { return n % 2 == 0; });
    
    cout << "Even numbers: ";
    for (auto n : evens) cout << n << " ";
    cout << endl;
    
    // ⚠️ 复杂逻辑考虑命名函数
    // auto complex_lambda = [](int x, int y, int z) {
    //     // 很多行代码...  // 不推荐
    // };
}

// 4. C++17 结构化绑定
void best_practice_structured_binding() {
    cout << "\n=== Best Practice 4: Structured Bindings (C++17) ===" << endl;
    
    map<string, int> scores = {{"Alice", 95}, {"Bob", 87}, {"Charlie", 92}};
    
    // ❌ C++11 方式
    // for (auto it = scores.begin(); it != scores.end(); ++it) {
    //     cout << it->first << ": " << it->second << endl;
    // }
    
    // ✅ C++17 结构化绑定
    for (const auto& [name, score] : scores) {
        cout << name << ": " << score << endl;
    }
}

// 5. std::optional 处理可选值
optional<int> find_first_even(const vector<int>& vec) {
    for (int n : vec) {
        if (n % 2 == 0) return n;
    }
    return nullopt;
}

void best_practice_optional() {
    cout << "\n=== Best Practice 5: std::optional (C++17) ===" << endl;
    
    vector<int> numbers = {1, 3, 5, 7, 8, 9};
    
    // ❌ C++98 方式（不安全）
    // int* result = find(...);  // 可能返回 nullptr
    // if (result) { ... }
    
    // ✅ C++17 optional
    if (auto result = find_first_even(numbers); result) {
        cout << "First even: " << *result << endl;
    } else {
        cout << "No even number found" << endl;
    }
}

// 6. std::variant 类型安全的联合体
void best_practice_variant() {
    cout << "\n=== Best Practice 6: std::variant (C++17) ===" << endl;
    
    // ❌ C 风格 union（不安全）
    // union { int i; double d; char c; };
    
    // ✅ C++17 variant
    variant<int, double, string> v;
    
    v = 42;
    cout << "Integer: " << get<int>(v) << endl;
    
    v = 3.14;
    cout << "Double: " << get<double>(v) << endl;
    
    v = "Hello";
    cout << "String: " << get<string>(v) << endl;
    
    // 访问者模式
    visit([](auto&& arg) {
        cout << "Visit: " << arg << endl;
    }, v);
}

// 7. constexpr 编译时计算
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

void best_practice_constexpr() {
    cout << "\n=== Best Practice 7: constexpr ===" << endl;
    
    // ❌ 运行时计算
    // const int size = factorial(5);
    
    // ✅ 编译时计算
    constexpr int size = factorial(5);
    int array[size];  // 数组大小在编译时确定
    
    cout << "factorial(5) = " << size << endl;
}

// 8. 使用 emplace 而非 push
void best_practice_emplace() {
    cout << "\n=== Best Practice 8: emplace vs push ===" << endl;
    
    vector<pair<int, string>> vec;
    
    // ❌ push_back：构造临时对象再拷贝
    // vec.push_back(make_pair(1, "one"));
    
    // ✅ emplace_back：直接在容器中构造
    vec.emplace_back(1, "one");
    vec.emplace_back(2, "two");
    
    for (const auto& [num, name] : vec) {
        cout << num << ": " << name << endl;
    }
}

// 9. 使用 = delete 禁止特殊成员函数
class NonCopyable {
public:
    NonCopyable() = default;
    NonCopyable(const NonCopyable&) = delete;  // 禁止拷贝
    NonCopyable& operator=(const NonCopyable&) = delete;
    NonCopyable(NonCopyable&&) = default;  // 允许移动
    NonCopyable& operator=(NonCopyable&&) = default;
};

// 10. 使用 override 和 final
class Base {
public:
    virtual void foo() { cout << "Base::foo" << endl; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void foo() override {  // ✅ 显式标记覆盖
        cout << "Derived::foo" << endl;
    }
};

int main() {
    cout << "======================================" << endl;
    cout << "  Modern C++ Best Practices (C++11/14/17)" << endl;
    cout << "======================================" << endl;
    
    best_practice_smart_pointers();
    best_practice_auto();
    best_practice_lambda();
    best_practice_structured_binding();
    best_practice_optional();
    best_practice_variant();
    best_practice_constexpr();
    best_practice_emplace();
    
    cout << "\n======================================" << endl;
    cout << "Follow these practices for safer, cleaner code!" << endl;
    cout << "======================================" << endl;
    
    return 0;
}
