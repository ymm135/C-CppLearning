// Chapter 2 - C++ 类型学习示例
#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

int main()
{
    // 设置本地化环境，支持中文
    std::locale::global(std::locale(""));
    std::cout.imbue(std::locale());
    
#ifdef _WIN32
    // 设置Windows控制台为UTF-8编码
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    // 启用虚拟终端处理，改善CLion终端的UTF-8支持
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    char a[10] = "a";
    short int s = 97;
    int m = 97;
    long int n = 97;
    float f = 97.0f;
    double d = 97.0;
    long double k = 97.0;
    bool b = true;
    wchar_t w[10] = L"a";

    // 输出各种类型的值
    std::cout << "=== C++ 基本类型示例 ===" << std::endl;
    std::cout << "char a[10] = \"a\"        | 值: " << a << " | 大小: " << sizeof(a) << " 字节" << std::endl;
    std::cout << "short int s = 97         | 值: " << s << " | 大小: " << sizeof(s) << " 字节" << std::endl;
    std::cout << "int m = 97               | 值: " << m << " | 大小: " << sizeof(m) << " 字节" << std::endl;
    std::cout << "long int n = 97          | 值: " << n << " | 大小: " << sizeof(n) << " 字节" << std::endl;
    std::cout << "float f = 97.0f          | 值: " << f << " | 大小: " << sizeof(f) << " 字节" << std::endl;
    std::cout << "double d = 97.0          | 值: " << d << " | 大小: " << sizeof(d) << " 字节" << std::endl;
    std::cout << "long double k = 97.0     | 值: " << k << " | 大小: " << sizeof(k) << " 字节" << std::endl;
    std::cout << "bool b = true            | 值: " << (b ? "true" : "false") << " | 大小: " << sizeof(b) << " 字节" << std::endl;
    std::wcout << L"wchar_t w[10] = L\"a\"    | 值: " << w << L" | 大小: " << sizeof(w) << L" 字节" << std::endl;

    return 0;
}