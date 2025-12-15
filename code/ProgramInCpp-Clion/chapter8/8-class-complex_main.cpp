#include "Complex.h"
#include <iostream>

using namespace std;

int main() {
    cout << "=== Complex Number Operations Demo ===" << endl;
    
    // 1. 构造函数测试
    Complex c1;              // 默认构造
    Complex c2(3.0, 4.0);    // 带参数构造
    Complex c3(c2);          // 拷贝构造
    
    cout << "\nc1 (default): " << c1 << endl;
    cout << "c2 (3, 4):    " << c2 << endl;
    cout << "c3 (copy c2): " << c3 << endl;
    
    // 2. 算术运算
    Complex c4 = c2 + c3;
    cout << "\nc2 + c3 = " << c4 << endl;
    
    Complex c5 = c2 - Complex(1, 1);
    cout << "c2 - (1,1) = " << c5 << endl;
    
    Complex c6 = c2 * Complex(2, 0);
    cout << "c2 * (2,0) = " << c6 << endl;
    
    // 3. 复合赋值
    Complex c7(5, 5);
    c7 += c2;
    cout << "\nc7 after += c2: " << c7 << endl;
    
    // 4. 比较运算
    cout << "\nc2 == c3: " << (c2 == c3 ? "true" : "false") << endl;
    cout << "c2 != c3: " << (c2 != c3 ? "true" : "false") << endl;
    
    // 5. 自增自减
    Complex c8(10, 10);
    cout << "\nc8: " << c8 << endl;
    cout << "++c8: " << ++c8 << endl;
    cout << "c8++: " << c8++ << endl;
    cout << "c8 now: " << c8 << endl;
    
    // 6. 输入测试（可选，注释掉避免阻塞）
    // Complex c9;
    // cout << "\nEnter complex number (real imag): ";
    // cin >> c9;
    // cout << "You entered: " << c9 << endl;
    
    cout << "\n=== Demo Complete ===" << endl;
    
    return 0;
}
