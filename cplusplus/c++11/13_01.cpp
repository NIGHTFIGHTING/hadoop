#include <iostream>
#include <map>

using namespace std;


template <typename T1, typename T2>
//decltype(x+y) add(T1 x, T2 y);
auto add(T1 x, T2 y) -> decltype(x+y);

template <typename T>
void test_decltype(T obj) {
	map<string, float>::value_type elem1;

	map<string, float> coll;
	decltype(coll)::value_type elem2;

	typedef typename decltype(obj)::iterator iType;
	//typedef typename T::iterator iType;
	
	decltype(obj) another(obj);
}


int main() {
	map<string, float> coll;
	decltype(coll)::value_type elem;

	map<string, float>::value_type elem1;
	cout << typeof(elem1) << endl;
	return 0;
}
