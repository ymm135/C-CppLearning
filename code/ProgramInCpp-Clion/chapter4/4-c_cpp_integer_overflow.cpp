#include <iostream>
#include <exception>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;

int main() {
    try {

        cout << "=== use int overflow ===" << endl;
        
        int i = 2147483647;
        cout << "INT_MAX + 1 = " << ++i << endl;

        int a = 500;
        int b = 400;
        int c = 300;
        int d = 200;
        cout << "500*400*300*200 = " << a*b*c*d << endl;

        // 使用 Boost cpp_int - 无溢出
        cout << "=== usb cpp_int no overflow ===" << endl;
        
        cpp_int big_i = 2147483647;
        ++big_i;
        cout << "INT_MAX + 1 = " << big_i << endl;

        cpp_int big_a = 500;
        cpp_int big_b = 400;
        cpp_int big_c = 300;
        cpp_int big_d = 200;
        cout << "500*400*300*200 = " << big_a*big_b*big_c*big_d << endl;

        cout << "done !!!" << endl;
        
    } catch (const exception& e) {
        cerr << "错误: " << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "未知错误" << endl;
        return 1;
    }

    return 0;
}