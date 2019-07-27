#include <iostream>

using namespace std;

class Zoo {
public:
};

//NoCopy��ֹʹ��delete���̳е���Ҳ����ʹ��delete
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

//�����ֹʹ��copy,assignment�����Ǽ̳е�friend�����ʹ��copy��assignment
//����ֹ��private,=delete
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
