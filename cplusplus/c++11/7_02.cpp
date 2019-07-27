#include <iostream>

using namespace std;

class P {
public:
	P(int a, int b) {
		cout << "P(int a, int b)" << endl;
	}
	
	/*explicit*/ P(initializer_list<int>) {
		cout << "P(initializer_list<int>)" << endl;
	}
	
	explicit P(int a, int b ,int c) {
		cout << "explicit P(int a, int b ,int c)" <<endl;
	}
};

void fp(const P &) {
	cout << "void fp(const P &)" << endl;
}

int main() {
	P p1 (77, 5); //使用P(int a, int b)
        P p2 {77, 5}; // 使用P(initializer_list<int>)；因为使用initializer_list<int>构造
	P p3 {77, 5, 42}; // 使用P(initializer_list<int>)；因为使用initializer_list<int>构造
	//P p4 = {77, 5}; // 使用P(initializer_list<int>)；因为没有 explicit initializer_list<int>
	//P p5 = {77, 5, 42};
	
	fp( {47, 11} );
	//explicit P(initializer_list<int>)
	//error: converting to 'const P' from initializer list would use explicit constructor 'P::P(std::initializer_list<int>)
	fp( {47, 11, 3} );
	
	P p11 {77, 5, 42, 500}; //P(initializer_list<int>)
	P p12 = {77, 5, 42, 500}; 
	//P(initializer_list<int>) ---> right
	//explicit P(initializer_list<int>) ---> wrong
	P p13 {10}; //P(initializer_list<int>)
	return 0;
}
