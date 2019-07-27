#include <iostream>

using namespace std;

class CChild;

class CParent {
private :
	CParent(int a):_a(a) {}
	CParent() {};
	~CParent() {}
public:
	friend class CChild;
private:
	int _a;
public:
	void Print() {
		cout << _a << endl;
	}
};

class CChild : public CParent {
public:
	CChild()=default;
	CChild(int a):CParent(a) {}
	~CChild()=default;
};


int main() {
	//CParent parent;  //CParent 类构造函数私有private,不能进构造
	CChild child;  //CChild 类是CParent类友元
	CChild child1(3);
	child1.Print();
	return 0;
}
