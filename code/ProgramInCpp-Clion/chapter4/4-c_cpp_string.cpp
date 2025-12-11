# include <iostream>
using namespace std;

int main()
{
	char c1 = 'yes'; // 会截断,有的编译器取第一个,有的编译器取最后一个
	cout << c1 << endl;

	char c2 = 'y'; // 双引号是字符串, "yes" => 'y'和'\0'
	// char c2 = "yes"; // 双引号是字符串,

	const char* slash = "/"; // 这里是一个字符串,这是给的一个地址空间给到指针.
	// const char* slash2 = '/ '; // 把字符给到一个指针.
	const char* slash2 = &c1;
	cout << slash2 << endl;

	string s1(1,'yes'); // s
	cout << s1 << endl;

	string s2(3,'yes');// sss
	cout << s2 << endl;

	string s3(3,'y');// yyy
	cout << s3 << endl;

	string s4("/");// /
	cout << s4 << endl;

	string s5(1, '/');// /
	cout << s5 << endl;

	string s6("yes");
	cout << s6 << endl; // yes

    return 0;
}