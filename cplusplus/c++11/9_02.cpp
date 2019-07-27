#include <iostream>

using namespace std;

class Foo {
public:
	Foo(int i):_i(i) {}
	Foo()=default;
	
	Foo(const Foo &x):_i(x._i) {}
	//Foo(const Foo &x)=default; //error: 'Foo::Foo(const Foo&)' cannot be overloaded
	//Foo(const Foo &x)=delete;  //error: 'Foo::Foo(const Foo&)' cannot be overloaded

	Foo& operator=(const Foo &x) { _i = x._i; return (*this); }
	//Foo& operator=(const Foo &x)=default;
	//Foo& operator=(const Foo &x)=delete;
	
	//void fun1()=default;
	void fun2()=delete;

	//~Foo()=delete;  //error: use of deleted function 'Foo::~Foo()'
	~Foo()=default;

private:
	int _i;
};

int main() {
	Foo x;
	return 0;
}
