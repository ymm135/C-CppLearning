// Chapter 4 - 测试用例1：字符串操作
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
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif

    std::cout << "=== 测试用例1: 字符串操作 ===" << std::endl;
    std::cout << "这是第一个测试用例" << std::endl;
    
    return 0;
}
