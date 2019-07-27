#include <iostream>

using namespace std;


struct Complex {
	int real,imag;
	
	Complex(int re, int im=0):real(re),imag(im) {
	}

	//explicit for ctors talking one argument
	//non-explicit one-argument can use 
	/*explicit Complex(int re, int im=0):real(re),imag(im) {
	}*/
	
	Complex operator+(const Complex &x) {
		return Complex((real+x.real),(imag+x.imag));
	}
	void Print() {
		cout << "real:" << real << " imag:" << imag <<endl;
	}
};

int main() {
	Complex c1(12.5);
	c1.Print();
	//Complex c2 = c1 + Complex(5); /*ÏÔÊ¾Ç¿ÖÆ×ª»»*/
	Complex c2 = c1 + 5; /*ÒýÊ¾×ª»»*¾*/
	c2.Print();
	return 0;
}
