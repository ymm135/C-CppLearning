#include "Complex.h"

Complex::Complex()
{
	_real = 0.0;
	_image = 0.0;
	DEBUG_LOG("Default Constructor: Complex() -> (" << _real << ", " << _image << ")");
}

Complex::Complex(double r, double i)
{
	_real = r;
	_image = i;
	DEBUG_LOG("Constructor: Complex(" << r << ", " << i << ") -> (" << _real << ", " << _image << ")");
}

Complex::Complex(const Complex& c)
{
	_real = c._real;
	_image = c._image;
	DEBUG_LOG("Copy Constructor: Complex(copying (" << c._real << ", " << c._image << ")) -> (" << _real << ", " << _image << ")");
}

Complex& Complex::operator= (const Complex& c)
{
	if (this != &c)
	{
		DEBUG_LOG("Assignment operator: (" << _real << ", " << _image << ") = (" << c._real << ", " << c._image << ")");
		_real = c._real;
		_image = c._image;
	}
	else
	{
		DEBUG_LOG("Assignment operator: Self-assignment detected, skipped");
	}
	return *this;
}

Complex::~Complex()
{
	DEBUG_LOG("Destructor: ~Complex() releasing object (" << _real << ", " << _image << ")");
	_real = _image = 0.0;
}

Complex Complex::operator+ (const Complex& c) const
{
	DEBUG_LOG("Addition: (" << _real << ", " << _image << ") + (" << c._real << ", " << c._image << ") = (" << (_real + c._real) << ", " << (_image + c._image) << ")");
	return Complex(_real + c._real, _image + c._image);
}


Complex& Complex::operator+= (const Complex& c)
{
	DEBUG_LOG("Compound addition: (" << _real << ", " << _image << ") += (" << c._real << ", " << c._image << ")");
	_real += c._real;
	_image += c._image;
	DEBUG_LOG("  Result: (" << _real << ", " << _image << ")");
	return *this;
}

Complex Complex::operator-(const Complex &c) const
{
	return Complex(_real - c._real, _image - c._image);
}

Complex& Complex::operator-=(const Complex &c)
{
	_real -= c._real;
	_image -= c._image;

	return *this;
}

Complex Complex::operator*(const Complex &c) const
{
	return Complex(_real*c._real - _image*c._image, _real*c._image + _image*c._real);
}

Complex& Complex::operator*=(const Complex &c)
{
	Complex tmp(*this);  //拷贝构造函数
	_real = tmp._real*c._real - _image*c._image;
	_image = tmp._real*c._image + tmp._image*c._real;
	return *this;
}

Complex Complex::operator/(const Complex &c) const
{
	double t = c._real*c._real + c._image*c._image;
	return Complex((_real*c._real - _image*(-c._image)) / t, (_real*(-c._image) + _image*c._real) / t);
}

Complex& Complex::operator/=(const Complex &c)
{
	Complex tmp(*this);  //拷贝构造函数
	double t = c._real*c._real + c._image*c._image;
	_real = (tmp._real*c._real - tmp._image*(-c._image)) / t;
	_image = (tmp._real*(-c._image) + tmp._image*c._real) / t;
	return *this;
}

bool Complex::operator==(const Complex& c) const
{
	return (_real == c._real) && (_image == c._image);
}

bool Complex::operator!=(const Complex& c) const
{
	return !( (_real == c._real) && (_image == c._image) );
}

bool Complex::operator>(const Complex &c)  const
{
	return (_real > c._real) && (_image > c._image);
}

bool Complex::operator>=(const Complex &c) const
{
	return (_real >= c._real) && (_image >= c._image);
}

bool Complex::operator<(const Complex &c) const
{
	return (_real < c._real) && (_image < c._image);
}

bool Complex::operator<=(const Complex &c) const
{
	return (_real <= c._real) && (_image <= c._image);
}


Complex& Complex::operator++ () // 前置++
{
	_real++;
	_image++;
	return *this;
}

Complex Complex::operator++ (int) // 后置++
{
	//Complex tmp(*this);
	//_real++;
	//_image++;
	//return tmp;
	return Complex(_real++, _image++);
}

Complex& Complex::operator--()   //前置--
{
	_real--;
	_image--;
	return *this;
}

Complex Complex::operator--(int) //后置--
{
	return Complex(_real--, _image--);
}

ostream& operator<<(ostream& os, const Complex &x)
{
	os << "real value is  " << x._real << "  image value is " << x._image;
	return os;
}

istream& operator >> (istream& is, Complex &x)
{
	is >> x._real >> x._image;
	return is;
}