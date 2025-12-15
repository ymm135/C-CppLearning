#include <string>
#include <iostream>
#include <memory>
using namespace std;
int main()
{
    {
        // C++17 已移除 auto_ptr，改用 unique_ptr
        // unique_ptr 更安全：禁止拷贝，只能移动
        unique_ptr<int> pI(new int(10));
        cout << *pI << endl;                // 10

        // unique_ptr vs auto_ptr:
        // auto_ptr: 拷贝时会转移所有权（不安全，已废弃）
        // unique_ptr: 禁止拷贝，只能通过 move() 显式转移所有权
        unique_ptr<string> languages[5] = {
            unique_ptr<string>(new string("C")),
            unique_ptr<string>(new string("Java")),
            unique_ptr<string>(new string("C++")),
            unique_ptr<string>(new string("Python")),
            unique_ptr<string>(new string("Rust"))
        };
        cout << "There are some computer languages here first time: \n";
        for (int i = 0; i < 5; ++i)
        {
            cout << *languages[i] << endl;
        }
        unique_ptr<string> pC;
        pC = move(languages[2]); // 显式移动所有权（必须使用 move()）
        // 此时 languages[2] 不再引用该字符串，变成空指针
        
        cout << "There are some computer languages here second time: \n";
        for (int i = 0; i < 2; ++i)
        {
            cout << *languages[i] << endl;
        }
        cout << "The winner is " << *pC << endl;
        
        // 注意：访问已移动的 languages[2] 会导致崩溃
        //cout << "There are some computer languages here third time: \n";
        //for (int i = 0; i < 5; ++i)
        //{
        //    cout << *languages[i] << endl;  // i=2 时会崩溃！
        //}
    }
    return 0;
}