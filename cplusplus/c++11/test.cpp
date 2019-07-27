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
	//CParent parent;  //CParent �๹�캯��˽��private,���ܽ�����
	CChild child;  //CChild ����CParent����Ԫ
	CChild child1(3);
	child1.Print();
	return 0;
}
