#include <iostream>
using namespace std;

// 简单的Lambda示例 - 用于查看编译器生成的代码
int main() {
    // 1. 无捕获的Lambda
    auto lam1 = [](int a) {
        cout << "Lambda: " << a << endl;
    };
    
    // 2. 捕获变量的Lambda
    int factor = 10;
    auto lam2 = [factor](int x) {
        return x * factor;
    };
    
    // 3. 引用捕获
    int count = 0;
    auto lam3 = [&count]() {
        count++;
    };
    
    // 使用Lambda
    lam1(42);
    cout << "Result: " << lam2(5) << endl;
    lam3();
    cout << "Count: " << count << endl;
    
    return 0;
}
