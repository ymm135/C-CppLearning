// AboutString.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
using namespace std;

static const int MAX_LEN = 30;
int main()
{
	char str1[] = "string";
	cout << strlen(str1) << endl;
	cout << sizeof(str1) / sizeof(str1[0]) << endl;

	char str2[] = "stri\0ng";
	cout << strlen(str2) << endl;
	cout << sizeof(str2) / sizeof(str2[0]) << endl;

	char str1A[MAX_LEN] = "stringA";
	strcat(str1A, str2);
	cout << str1A << endl;
	cout << strlen(str1A) << endl;
	cout << sizeof(str1A) / sizeof(str1A[0]) << endl;

	cout << endl;
	cout << "Testing C++ String: " << endl;
	string sstr1 = "string";
	cout << sstr1.length() << endl;
	cout << sstr1.capacity() << endl;
	cout << sizeof(sstr1) << endl;

	cout << "sstr2: " << endl;
	string sstr2 = "stri\0ng";
	cout << sstr2.length() << endl;
	cout << sstr2.capacity() << endl;
	cout << sizeof(sstr2) << endl;

	cout << "sstr1: " << endl;
	sstr1 += sstr2;
	cout << sstr1.length() << endl;
	cout << sstr1.capacity() << endl;
	cout << sizeof(sstr1) << endl;
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
