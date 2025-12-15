#include <iostream>
using namespace std;

// ========== 调试模式开关 ==========
// 取消注释下面这行以启用详细调试日志
#define COMPLEX_DEBUG

#ifdef COMPLEX_DEBUG
    #define DEBUG_LOG(msg) cout << "[DEBUG] " << msg << endl
#else
    #define DEBUG_LOG(msg) /* 调试关闭 */
#endif
// ==================================

class Complex
{
public:
    Complex();                                    // 默认构造函数
    Complex(double r,  double i);      // 构造函数
    virtual ~Complex();                      // 析构函数
    Complex(const Complex& x);      // 拷贝构造
    Complex& operator=(const Complex &c); // =号运算符


    double GetReal( ) const { return _real; }
    void SetReal(double d) { _real = d; }
    double GetImage() const { return _image; }
    void SetImage(double i) { _image = i; }

    // 运算符重载
    Complex operator+(const Complex &c) const;
    Complex& operator+=(const Complex &c);
    Complex operator-(const Complex &c) const;
    Complex& operator-=(const Complex &c);
    Complex operator*(const Complex &c) const;
    Complex& operator*=(const Complex &c);
    Complex operator/(const Complex &c) const;
    Complex& operator/=(const Complex &c);

    bool operator==(const Complex &c) const;
    bool operator!=(const Complex &c) const;
    bool operator>(const Complex &c)  const;
    bool operator>=(const Complex &c) const;
    bool operator<(const Complex &c) const;
    bool operator<=(const Complex &c) const;


    // 前置和后置++
    Complex& operator++();   //前置++
    Complex operator++(int); //后置++
    Complex& operator--();   //前置--
    Complex operator--(int); //后置--

    //protected:

    friend ostream& operator<<(ostream& os, const Complex &x);
    friend istream& operator>>(istream& is, Complex &x);

private:
    double _real;             // 复数的实部
    double _image;         // 复数的虚部
};
