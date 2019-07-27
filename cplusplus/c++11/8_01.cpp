#include <iostream>
#include <vector>
#include <map>
using namespace std;

void Print(vector<int> &vec) {
	for(auto elem : vec) {
		cout << "elem:" << elem << ' ';
	}
	cout << endl;
}

class C {
public:
	/*explicit*/ C(const string &s):_s(s) {
	}
	friend ostream & operator<<(ostream &os, const C &c) {
		os << c._s;
		return os;
	}
public:
	string _s;
};

/*ostream & operator<<(ostream &os, const C &c) {
	os << c._s << endl;
	return os;
}*/

int main() {
	for(int i : { 1, 2, 3, 4, 70 }) {
		cout << "element:" << i << " ";
	}
	cout << endl;

	vector<int> vec;
	for(int i=0; i<20; i++) {
		vec.push_back(i*2);
	}
	Print(vec);

	for(vector<int>::iterator elem = vec.begin(); elem!=vec.end(); elem++)	{
		*elem = *elem * 3;
	}
	Print(vec);

	for(auto &elem : vec) {
		elem/=3;
		//cout << elem << ' ';
	}
	Print(vec);

	map<int, int> MAP1;
	MAP1[100]=100;
	map<int, int>::iterator ite1 = MAP1.begin();
	cout << "ite1->first:" << ite1->first << " ite1->second:" << ite1->second << endl;
	map<int,int> MAP2;
	MAP2[100]=200;
	map<int, int>::iterator ite2 = MAP2.begin();
	cout << "ite2->first:" << ite2->first << " ite2->second:" << ite2->second << endl;
	//(*ite1) = (*ite2);  //关联容器不能 使用迭代器 直接改变元素

	//begin(), end()全局函数 C++2.0
	for(auto ite = begin(MAP1); ite!=end(MAP1); ++ite) {
		cout << ite->first << ' ' << ite->second << endl;
	}

	vector<string> vs;
	vs.push_back("a");
 	const C c {"pp\\"};
	cout<<c<<endl;
	//explicit C(string s);
	//invalid initialization of reference of type 'const C&' from expression of type 'std::basic_string<char>'
	for(const C& elem : vs) {
		cout<< elem <<endl;
	}
}
