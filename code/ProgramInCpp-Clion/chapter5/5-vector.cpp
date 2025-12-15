#include <iostream>
#include <vector>
using namespace std;

int main()
{
    // 创建动态数组vector
    vector<int> vec = { 1,2,3,4 };
    cout << "size is " << vec.size() << ",";
    cout << "capacity is " << vec.capacity() << endl;
    // 遍历所有元素
    for (int index = 0; index < vec.size(); ++index)
    {
        cout << vec[index] << ",";
    }
    cout << endl;

    // 在尾部插入一个元素5
    vec.push_back(5);
    cout << "size is " << vec.size() << ",";
    cout << "capacity is " << vec.capacity() << endl;
    // 遍历所有元素
    for (int index = 0; index < vec.size(); ++index)
    {
        cout << vec[index] << ",";
    }
    cout << endl;

    // 在中间插入一个元素6
    vec.insert(--vec.end(), 6);
    cout << "size is " << vec.size() << ",";
    cout << "capacity is " << vec.capacity() << endl;
    // 遍历所有元素
    for (int index = 0; index < vec.size(); ++index)
    {
        cout << vec[index] << ",";
    }
    cout << endl;

    // 在尾部移除一个元素
    vec.pop_back();
    cout << "size is " << vec.size() << ",";
    cout << "capacity is " << vec.capacity() << endl;
    // 遍历所有元素
    for (int index = 0; index < vec.size(); ++index)
    {
        cout << vec[index]<< ",";
    }
    cout << endl;

    // 在任意位置移除一个元素
    vec.erase(vec.end() - 2);
    cout << "size is " << vec.size() << ",";
    cout << "capacity is " << vec.capacity() << endl;
    // 遍历所有元素
    for (int index = 0; index < vec.size(); ++index)
    {
        cout << vec[index] << ",";
    }
    cout << endl;

    return 0;
}
