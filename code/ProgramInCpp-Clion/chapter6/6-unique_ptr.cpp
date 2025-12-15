#include <iostream>
#include <memory>  // C++11+ 使用 unique_ptr
#include <string>

using namespace std;

int main() {
    // C++17 不再支持 auto_ptr，改用 unique_ptr
    // auto_ptr 在 C++11 被废弃，C++17 被移除
    
    unique_ptr<int> pI(new int(12));
    cout << "*pI: " << *pI << endl;
    
    // unique_ptr 的优势：
    // 1. 禁止拷贝，只能移动（更安全）
    // 2. 可以用于数组
    // 3. 自定义删除器
    
    // 创建字符串智能指针数组
    unique_ptr<string> languages[5] = {
        unique_ptr<string>(new string("C")),
        unique_ptr<string>(new string("C++")),
        unique_ptr<string>(new string("Java")),
        unique_ptr<string>(new string("Python")),
        unique_ptr<string>(new string("Golang"))
    };
    
    // 输出所有语言
    for (int i = 0; i < 5; i++) {
        cout << *languages[i] << endl;
    }
    
    // 移动语义示例（unique_ptr 不能拷贝，只能移动）
    unique_ptr<string> pC = move(languages[0]);  // 移动所有权
    cout << "\nMoved pointer: " << *pC << endl;
    
    // languages[0] 现在为空
    if (!languages[0]) {
        cout << "languages[0] is now empty after move" << endl;
    }
    
    // 使用 make_unique (C++14+) - 更推荐的方式
    auto pStr = make_unique<string>("Modern C++");
    cout << "\nCreated with make_unique: " << *pStr << endl;
    
    return 0;
}
