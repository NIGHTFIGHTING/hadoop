#include <iostream>

using namespace std;

class Zoo {
public:
};

//NoCopy禁止使用delete，继承的类也不能使用delete
struct NoCopy {
	NoCopy()=default;
	NoCopy(const NoCopy &)=delete; //no copy
	NoCopy&operator=(const NoCopy &)=delete;  // no assignment
	~NoCopy()=default;
};

struct NoDtor {
	NoDtor()=default;
	~NoDtor()=delete;
};

class Foo;

//该类禁止使用copy,assignment，但是继承的friend类可以使用copy，assignment
//若禁止则private,=delete
class PrivateCopy {
private:
	PrivateCopy(const PrivateCopy &){};
	PrivateCopy &operator=(const PrivateCopy&) {};
public:
	PrivateCopy()=default;
	~PrivateCopy()=default;
public:
	friend class Foo;
};


class Foo: public PrivateCopy {
};

int main() {

	//NoDtor d;
	//NoDtor *d1 = new NoDtor();
	//delete d1;
	//PrivateCopy p;
	//PrivateCopy p1(p);
	Foo f;
	Foo f1(f);
	return 0;
}
