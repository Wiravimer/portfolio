#include <iostream>
#include <math.h>
#include <complex>
using namespace std;
const float Pi=3.14;

class Complex
{
	private:
	float real,mnim;

	public:

	Complex()//конструктор по умолчанию;
	{
		real=mnim=0;
	}

	Complex(float a)//конструктор преобразования базового типа к типу, определяемому разрабатываемым классом;
	{
		real = mnim = a;
	}

	Complex(float par_real,float par_mnim)//конструктор инициализации;
	{
		real = par_real;
		mnim = par_mnim;
	}

	friend Complex operator + (Complex,Complex);//Перегрузка оператора (+)
	friend Complex operator / (Complex,Complex);//Перегрузка оператора (/)
	friend Complex operator - (Complex,Complex);//Перегрузка оператора (-)
	friend Complex exp ( Complex operand);//Перегрузка функции exp
	friend ostream& operator << (ostream&,Complex&);//Перегрузка оператора (<<)
	//friend istream& operator >> (istream&,Complex&);//Перегрузка оператора (>>)
	friend Complex th(Complex z);
};

Complex operator + ( Complex l_operand, Complex r_operand)
{
	return Complex (l_operand.real+r_operand.real,  l_operand.mnim+r_operand.mnim);
}

Complex operator / ( Complex l_operand, Complex r_operand)
{
	return Complex (l_operand.real/r_operand.real,  l_operand.mnim/r_operand.mnim);
}

Complex operator - ( Complex l_operand, Complex r_operand)
{
	return Complex (l_operand.real-r_operand.real,  l_operand.mnim-r_operand.mnim);
}

Complex exp ( Complex operand)
{
	return Complex (operand.real=exp(operand.real)*cos(operand.mnim),
					operand.mnim=exp(operand.real)*sin(operand.mnim));
}

ostream& operator << (ostream & vivod, Complex &operand)
{
	vivod << operand.real << " + " << operand.mnim << "i" ;
	return vivod;
}

//istream& operator >> (istream & vvod, Complex &operand)
//{
//	vvod >> operand.real >> operand.mnim;
//	return vvod;
//}

Complex my_complex(Complex z)
{ 
	Complex y;
	y=4.6/th(z)-exp(2.2-z);
	return y;
}

Complex th(Complex z)
{
	Complex y;
	y.real=sinh(2*z.real) / (cosh(2*z.real)+cos(2*z.mnim));
	y.mnim=sin (2*z.mnim) / (cosh(2*z.real)+cos(2*z.mnim));
	return y;
}

complex <float> standart_complex (complex <float> z)
{
	complex <float> y;
	complex <float> a = 4.6;
	complex <float> b = 2.2;
	y=a/tanh(z)-exp(b-z);
	return y;
}



void table()
{
	
	for (float i = 1; i <= 2*Pi; i+=Pi/4)
	{
		Complex my_temp = my_complex(i);
		complex <float> standart_temp=standart_complex(i);
		cout << my_temp << "  |  "<<standart_temp<<endl;
	}

}

void main()
{setlocale(LC_ALL, "rus");

	table();
	system("pause");

} 



