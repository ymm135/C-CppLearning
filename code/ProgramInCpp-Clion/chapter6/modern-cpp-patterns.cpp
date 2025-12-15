#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include <string>
#include <optional>
#include <variant>
#include <map>

using namespace std;

// ===========================================
// Modern C++ Best Practices & Patterns
// ===========================================

// 1. Smart Pointers - Always prefer over raw pointers
void pattern_smart_pointers() {
    cout << "\n=== Pattern 1: Smart Pointer Usage ===" << endl;
    
    // unique_ptr for exclusive ownership
    auto data = make_unique<string>("Important Data");
    cout << "unique_ptr: " << *data << endl;
    
    // shared_ptr when sharing is needed
    auto shared1 = make_shared<int>(100);
    auto shared2 = shared1;  // Shared ownership
    cout << "shared_ptr count: " << shared1.use_count() << endl;
    
    // Transfer ownership with move
    auto transferred = move(data);
    // data is now empty (nullptr)
}

// 2. RAII Pattern with Smart Pointers
class Resource {
    string name;
public:
    explicit Resource(string n) : name(move(n)) {
        cout << "  [Resource] Acquired: " << name << endl;
    }
    ~Resource() {
cout << "  [Resource] Released: " << name << endl;
    }
    void use() { cout << "  [Resource] Using: " << name << endl; }
};

void pattern_raii() {
    cout << "\n=== Pattern 2: RAII (Resource Acquisition Is Initialization) ===" << endl;
    {
        auto res = make_unique<Resource>("Database Connection");
        res->use();
        // Automatic cleanup when scope ends
    }
    cout << "  Resource automatically cleaned up!" << endl;
}

// 3. Lambda Expressions for Algorithms
void pattern_lambdas() {
    cout << "\n=== Pattern 3: Lambda with STL Algorithms ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    
    // Filter evens
    vector<int> evens;
    copy_if(numbers.begin(), numbers.end(), back_inserter(evens),
        [](int n) { return n % 2 == 0; });
    
    cout << "Even numbers: ";
    for (auto n : evens) cout << n << " ";
    cout << endl;
    
    // Transform with lambda
    vector<int> doubled;
    transform(numbers.begin(), numbers.end(), back_inserter(doubled),
        [](int n) { return n * 2; });
    
    cout << "Doubled: ";
    for (int i = 0; i < 5; ++i) cout << doubled[i] << " ";
    cout << "..." << endl;
}

// 4. C++17 Structured Bindings
void pattern_structured_bindings() {
    cout << "\n=== Pattern 4: Structured Bindings (C++17) ===" << endl;
    
    map<string, int> scores = {
        {"Alice", 95},
        {"Bob", 87},
        {"Charlie", 92}
    };
    
    // Clean iteration
    for (const auto& [name, score] : scores) {
        cout << "  " << name << ": " << score << endl;
    }
    
    // Decompose pairs/tuples
    auto [first, second] = make_pair("Key", 42);
    cout << "  Pair: " << first << " = " << second << endl;
}

// 5. std::optional for Optional Values
optional<int> findFirst(const vector<int>& vec, int value) {
    for (int x : vec) {
        if (x == value) return x;
    }
    return nullopt;
}

void pattern_optional() {
    cout << "\n=== Pattern 5: std::optional (C++17) ===" << endl;
    
    vector<int> numbers = {1, 3, 5, 7, 9};
    
    if (auto result = findFirst(numbers, 5); result) {
        cout << "  Found: " << *result << endl;
    } else {
        cout << "  Not found" << endl;
    }
    
    if (auto result = findFirst(numbers, 4); result) {
        cout << "  Found: " << *result << endl;
    } else {
        cout << "  Not found" << endl;
    }
}

// 6. std::variant for Type-Safe Unions
void pattern_variant() {
    cout << "\n=== Pattern 6: std::variant (C++17) ===" << endl;
    
    variant<int, double, string> value;
    
    value = 42;
    cout << "  Integer: " << get<int>(value) << endl;
    
    value = 3.14;
    cout << "  Double: " << get<double>(value) << endl;
    
    value = "Hello";
    cout << "  String: " << get<string>(value) << endl;
    
    // Visitor pattern
    visit([](auto&& arg) {
        cout << "  Visiting: " << arg << endl;
    }, value);
}

// 7. Emplace for Efficiency
void pattern_emplace() {
    cout << "\n=== Pattern 7: emplace vs push ===" << endl;
    
    vector<pair<int, string>> vec;
    
    // push_back: creates temporary then copies
    // vec.push_back(make_pair(1, "one"));
    
    // emplace_back: constructs in-place (more efficient)
    vec.emplace_back(1, "one");
    vec.emplace_back(2, "two");
    
    cout << "  Pairs created in-place efficiently" << endl;
    for (const auto& [num, str] : vec) {
        cout << "    " << num << ": " << str << endl;
    }
}

// 8. constexpr for Compile-Time Computation
constexpr int factorial(int n) {
    return n <= 1 ? 1 : n * factorial(n - 1);
}

void pattern_constexpr() {
    cout << "\n=== Pattern 8: constexpr Compilation ===" << endl;
    
    constexpr int fact5 = factorial(5);  // Computed at compile time!
    cout << "  factorial(5) = " << fact5 << " (compile-time)" << endl;
    
    // Can use in array sizes
    int arr[factorial(4)];
    cout << "  Array size: " << sizeof(arr) / sizeof(int) << endl;
}

// 9. Delete and Default Special Members
class NonCopyable {
public:
    NonCopyable() = default;
    ~NonCopyable() = default;
    
    // Explicitly delete copy operations
    NonCopyable(const NonCopyable&) = delete;
    NonCopyable& operator=(const NonCopyable&) = delete;
    
    // Allow move operations
    NonCopyable(NonCopyable&&) = default;
    NonCopyable& operator=(NonCopyable&&) = default;
};

void pattern_special_members() {
    cout << "\n=== Pattern 9: = delete and = default ===" << endl;
    
    NonCopyable obj1;
    // NonCopyable obj2 = obj1;  // Compile error!
    NonCopyable obj2 = move(obj1);  // OK
    cout << "  Object can be moved but notcopied" << endl;
}

// 10. override Keyword
class Base {
public:
    virtual void foo() { cout << "  Base::foo" << endl; }
    virtual ~Base() = default;
};

class Derived : public Base {
public:
    void foo() override {  // Explicit override
        cout << "  Derived::foo" << endl;
    }
    // void fooo() override;  // Compile error - no such virtual function!
};

void pattern_override() {
    cout << "\n=== Pattern 10: override Keyword ===" << endl;
    
    unique_ptr<Base> ptr = make_unique<Derived>();
    ptr->foo();  // Calls Derived::foo
}

int main() {
    cout << "============================================" << endl;
    cout << "  Modern C++ Best Practices & Patterns" << endl;
    cout << "  C++11/14/17 Features" << endl;
    cout << "============================================" << endl;
    
    pattern_smart_pointers();
    pattern_raii();
    pattern_lambdas();
    pattern_structured_bindings();
    pattern_optional();
    pattern_variant();
    pattern_emplace();
    pattern_constexpr();
    pattern_special_members();
    pattern_override();
    
    cout << "\n============================================" << endl;
    cout << "  Apply these patterns for modern, safe C++!" << endl;
    cout << "============================================" << endl;
    
    return 0;
}
