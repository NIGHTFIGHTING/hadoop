#include <iostream>
#include <vector>
#include <list>
#include <deque>


using namespace std;

template<typename T>
class MyAlloc {
};

template <typename T>
using Vec = vector<T, MyAlloc<T>>;

class MyString {
};

class MyStrNoMove {
};


template <typename T>
void output_static_data(const T& obj) {
}


template <typename Container>
void test_moveable(Container c) {
	typedef typename iterator_traits<typename Container::iterator>::value_type Valtype;
	
	for(long i=0; i<200000000000000; ++i) {
		c.insert(c.end(), Valtype());
	}

	output_static_data(*(c.begin()));
	Container c1(c);
	Container c2(std::move(c));
	c1.swap(c2);
}

int main() {

	//Vec<int> v;
	test_moveable(list<MyString>());
	test_moveable(list<MyStrNoMove>());
	return 0;
}
