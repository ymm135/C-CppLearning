#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <algorithm>
#include <string>

using namespace std;

// ===========================================
// C++98 vs Modern C++ - Side by Side Comparison
// ===========================================

void demo1_auto_type_deduction() {
    cout << "\n=== 1. Auto Type Deduction ===" << endl;
    
    vector<int> numbers = {1, 2, 3, 4, 5};
    
    // C++98: Verbose type declarations
    cout << "C++98 style:" << endl;
    vector<int>::iterator it98 = numbers.begin();
    cout << "  First element: " << *it98 << endl;
    
    // C++11: Auto type deduction
    cout << "C++11 style:" << endl;
    auto it11 = numbers.begin();
    cout << "  First element: " << *it11 << endl;
    
    // Even more useful with complex types
    map<string, vector<int>> complexMap;
    complexMap["test"] = {1, 2, 3};
    auto mapIt = complexMap.begin();  // Much cleaner!
}

void demo2_smart_pointers() {
    cout << "\n=== 2. Smart Pointers vs Raw Pointers ===" << endl;
    
    // C++98: Manual memory management (dangerous!)
    cout << "C++98 - Raw pointers:" << endl;
    {
        int* raw = new int(42);
        cout << "  Value: " << *raw << endl;
        delete raw;  // Easy to forget!
    }
    
    // C++11: unique_ptr (automatic cleanup)
    cout << "C++11 - unique_ptr:" << endl;
    {
        auto smart = make_unique<int>(42);
        cout << "  Value: " << *smart << endl;
        // No delete needed!
    }
    
    // C++11: shared_ptr (reference counting)
    cout << "C++11 - shared_ptr:" << endl;
    {
        auto s1 = make_shared<string>("Hello");
        {
            auto s2 = s1;  // Share ownership
            cout << "  Ref count: " << s1.use_count() << endl;  // 2
        }
        cout << "  Ref count: " << s1.use_count() << endl;  // 1
    }
}

void demo3_lambda_expressions() {
    cout << "\n=== 3. Lambda vs Function Objects ===" << endl;
    
    vector<int> numbers = {5, 2, 8, 1, 9, 3};
    
    // C++98: Function object (verbose!)
    struct Greater {
        bool operator()(int a, int b) const {
            return a > b;
        }
    };
    
    vector<int> v98 = numbers;
    sort(v98.begin(), v98.end(), Greater());
    cout << "C++98 sorted: ";
    for (size_t i = 0; i < 5; ++i) cout << v98[i] << " ";
    cout << endl;
    
    // C++11: Lambda expression (concise!)
    vector<int> v11 = numbers;
    sort(v11.begin(), v11.end(), [](int a, int b) {
        return a > b;
    });
    cout << "C++11 sorted: ";
    for (const auto& n : v11) {
        if (&n - &v11[0] >= 5) break;
        cout << n << " ";
    }
    cout << endl;
    
    // Lambda with capture
    int threshold = 5;
    auto count = count_if(numbers.begin(), numbers.end(),
        [threshold](int n) { return n > threshold; });
    cout << "Numbers > " << threshold << ": " << count << endl;
}

void demo4_range_based_for() {
    cout << "\n=== 4. Range-Based For Loop ===" << endl;
    
    vector<string> languages = {"C", "C++", "Python", "Java"};
    
    // C++98: Index-based loop
    cout << "C++98 style: ";
    for (size_t i = 0; i < languages.size(); ++i) {
        cout << languages[i] << " ";
    }
    cout << endl;
    
    // C++98: Iterator-based loop
    cout << "C++98 (iterator): ";
    for (vector<string>::iterator it = languages.begin();
         it != languages.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;
    
    // C++11: Range-based for
    cout << "C++11 style: ";
    for (const auto& lang : languages) {
        cout << lang << " ";
    }
    cout << endl;
}

void demo5_nullptr() {
    cout << "\n=== 5. nullptr vs NULL ===" << endl;
    
    // C++98: NULL is actually 0
    int* p98 = NULL;
    cout << "C++98: ptr is " << (p98 == 0 ? "null" : "not null") << endl;
    
    // C++11: nullptr is type-safe
    int* p11 = nullptr;
    cout << "C++11: ptr is " << (p11 == nullptr ? "null" : "not null") << endl;
    
    // Demonstrates type safety
    // void func(int);
    // void func(void*);
    // func(NULL);     // C++98: Ambiguous!
    // func(nullptr);  // C++11: Clearly calls func(void*)
}

void demo6_uniform_initialization() {
    cout << "\n=== 6. Uniform Initialization ===" << endl;
    
    // C++98: Multiple ways to initialize
    cout << "C++98:" << endl;
    int a = 10;
    int b(20);
    cout << "  a=" << a << ", b=" << b << endl;
    
    // C++11: Uniform brace initialization
    cout << "C++11:" << endl;
    int x{10};
    int y{20};
    vector<int> vec{1, 2, 3, 4, 5};
    map<string, int> m{{"one", 1}, {"two", 2}};
    
    cout << "  x=" << x << ", y=" << y << endl;
    cout << "  vec size: " << vec.size() << endl;
    cout << "  map size: " << m.size() << endl;
    
    // Prevents narrowing conversions
    // int narrow{3.14};  // Compile error!
}

// Demonstrate move semantics
class BigData {
    int* data;
    size_t size;
public:
    BigData(size_t s) : size(s) {
        data = new int[size];
        cout << "  [Constructed] BigData with " << size << " elements" << endl;
    }
    
    ~BigData() {
        delete[] data;
        cout << "  [Destroyed] BigData" << endl;
    }
    
    // C++11: Move constructor
    BigData(BigData&& other) noexcept
        : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
        cout << "  [Moved] BigData (no copy!)" << endl;
    }
    
    // Prevent copying
    BigData(const BigData&) = delete;
    BigData& operator=(const BigData&) = delete;
};

void demo7_move_semantics() {
    cout << "\n=== 7. Move Semantics ===" << endl;
    
    cout << "Creating object:" << endl;
    BigData data1(1000);
    
    cout << "Moving object:" << endl;
    BigData data2 = move(data1);
    
    cout << "Cleanup:" << endl;
    // data2 will be destroyed here
}

void demo8_constexpr() {
    cout << "\n=== 8. constexpr - Compile-Time Evaluation ===" << endl;
    
    // C++11: Compile-time constants
    constexpr int size = 10;
    constexpr int square(int x) { return x * x; }
    constexpr int result = square(5);
    
    cout << "Compile-time computed: square(5) = " << result << endl;
    
    // Can use in array size
    int arr[square(3)];  // Size 9, computed at compile time
    cout << "Array size: " << sizeof(arr) / sizeof(int) << endl;
}

int main() {
    cout << "============================================" << endl;
    cout << "  Modern C++ Features Demonstration" << endl;
    cout << "  C++98 vs C++11/14/17" << endl;
    cout << "============================================" << endl;
    
    demo1_auto_type_deduction();
    demo2_smart_pointers();
    demo3_lambda_expressions();
    demo4_range_based_for();
    demo5_nullptr();
    demo6_uniform_initialization();
    demo7_move_semantics();
    demo8_constexpr();
    
    cout << "\n============================================" << endl;
    cout << "  Modern C++ makes code safer and cleaner!" << endl;
    cout << "============================================" << endl;
    
    return 0;
}
