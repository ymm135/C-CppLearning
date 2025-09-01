// Demo9-8.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "jjalloc.h"
#include <vector>
using namespace std;

int main()
{
	int ia[5] = { 0, 1, 2, 3, 4 };
	unsigned int i;
	vector<int, JJ::allocator<int> > iv(ia, ia + 5);
	for (i = 0; i < iv.size(); i++)
	{
		cout << iv[i] << " ";
	}
	cout << endl;


    return 0;
}

