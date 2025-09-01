// AboutCasts.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
using  namespace std;

// 1+1/2+1/3+1/4+... +1/n
double getSum(int n)
{
	double result = 0.0;
	for (int i = 1; i < n + 1; i++)
	{
		//result += 1.0 / i;
		result += static_cast < double>(1) / i;
	}
	return result;
}


int main()
{
    //例子一
	int array[] = { 1,2,3 };
	cout << sizeof(array) / sizeof(array[0]) << endl;
	int threshold = -1;
	int len = static_cast <int>( sizeof(array) / sizeof(array[0]) ) ;
	//if (  sizeof(array) / sizeof(array[0]) > static_cast<unsigned int>(threshold)  )  //发生了一个隐式的类型转换
	if (len  > threshold)
	{
		cout << "positive number array" << endl;
	}
	else
	{
		cout << "negative number array" << endl;
	}
	cout << static_cast<unsigned int>(threshold) << endl;
	



	/*
   // 例子二
	// 1+1/2+1/3+1/4+... +1/n 
	int n = 0;
	cin >> n;
	cout << getSum(n) << endl;
	*/
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
