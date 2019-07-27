#include <iostream>
#include <vector>
#include <list>
#include <deque>
using namespace std;


class MyString {
};

class MyStrNoMove {
};


template<typename T,
		template<class T>
		class Container
 	>

class XCls {
private:
	Container<T> c;
public:
	XCls() {
		for(long i=0; i<200; ++i) {
			c.insert(c.end(),T());
		}
		
		Container<T> c1(c);
		Container<T> c2(std::move(c));
		c1.swap(c2);
	}

};


template <typename T>
using Vec = vector<T, allocator<T>>;

template <typename T>
using Lst = list<T, allocator<T>>;

template <typename T>
using Deq = deque<T, allocator<T>>;

int main() {

	XCls<MyString,Vec> c1;
	XCls<MyStrNoMove,Vec> c2;

	return 0;
}
