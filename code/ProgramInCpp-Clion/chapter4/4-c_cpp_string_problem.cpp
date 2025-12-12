#include <iostream>
#include <cstring>
using namespace std;

static const int MAX_LEN = 30;

int main() {
    char str[] = "Hello World!";
    cout << "strlen:" << strlen(str) << endl; // strlen:12
    cout << "sizeof:" <<  sizeof(str)/sizeof(str[0]) << endl; // sizeof:13

    char str2[] = "Hello\0 World!"; // 增加\0, 字符串被截断了。
    cout << "strlen:" << strlen(str2) << endl; // strlen:5
    cout << "sizeof:" <<  sizeof(str2)/sizeof(str[0]) << endl; // sizeof:14

    char str1A[MAX_LEN] = "stringA";
    strcat(str1A, str2);
    cout << "str1A:" << str1A << endl; // str1A:stringAHello
    cout << strlen(str1A) << endl; // 12
    cout << sizeof(str1A)/sizeof(str1A[0]) << endl; // 30
    cout << size(str1A) << endl; // 30 使用std::size

    string str3 = "stringA";
    cout << "str3: " << str3 << endl;
    cout << str3.length() << endl;
    cout << str3.capacity() << endl;

    string str4 = "stringB\0Hello";
    cout << "str4: " << str4 << endl;
    cout << str4.length() << endl;
    cout << str4.capacity() << endl;

    str3 += str4;
    cout << "str3: " << str3 << endl;
    cout << str3.length() << endl;
    cout << str3.capacity() << endl;
    return 0;
}