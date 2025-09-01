// AboutCharArray.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <vector>
using namespace std;


double average1(int* arr)
{
    double result = 0.0;
    int len = sizeof(arr) / sizeof(arr[0]);
    //cout << "In average1:  " << len << endl;

    for (int i = 0; i < len; i++)
    {
        result += arr[i];
    }

    return result / len;
}

double average2(int* arr, int len)
{
    double result = 0.0;
    //int len = sizeof(arr) / sizeof(arr[0]);
    //cout << "In average1:  " << len << endl;

    for (int i = 0; i < len; i++)
    {
        result += arr[i];
    }

    return result / len;
}

double average3(vector<int>& v)
{
    double result = 0.0;
    vector<int>::iterator it = v.begin();
    //auto it = v.begin();

    for (; it != v.end();  ++it)
    {
        result += *it;
    }

    return result / v.size();
}

double average2DV(vector<vector<int> >& vv)
{
    double result = 0.0;
    unsigned int size = 0;

    for (unsigned int i = 0; i < vv.size(); ++i)
    {
        for (unsigned int j = 0; j < vv[i].size(); ++j)
        {
            result += vv[i][j];
            size += 1;
            cout << vv[i][j] << " ";
        }
        cout << endl;
    }

    return result / size;
}
int main()
{
    int array1[] = { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110 };
    int len = sizeof(array1) / sizeof(array1[0]);
    //cout << "In main:  " << len << endl;
    cout << average1(array1) << endl;
    cout << average2(array1, len) << endl;

    vector<int> vt{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110 };
    cout << average3(vt);

    cout << endl;

    vector<vector<int> > vv2D{8, vector<int>(12,3) };
    cout << average2DV(vv2D);


    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
