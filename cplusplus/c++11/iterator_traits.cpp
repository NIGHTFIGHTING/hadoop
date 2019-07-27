#include <iostream>

using namespace std;

template<typename T>
struct MyIter {
	typedef T value_type;
	T *ptr;
	MyIter(T*p):ptr(p) {}
	T &operator*() { return (*ptr); }
};

template<typename I>
typename MyIter<I>::value_type value_type
	func(I ite) {
		return (*ite);
}

template<typename I>
struct iterator_traits<I*> {
	typename I value_type;
}

template<typename I> 
struct iterator_traits {
	typename MyIter<I>::value_type value_type;
}

template<typename I>
typename iterator_traits<I>::value_type value_type
	func1(I ite) {
		return (*ite);
}

int main() {
	MyIter<int> ite(new int (9));
	//cout << func(ite);
	//int value = func(ite);
	return 0;
}
