#include <iostream>
#include <bitset>
#include <tuple>

using namespace std;


template<int IDX, int MAX,typename... Args>
struct PRINT_TUPLE {
	static void print(ostream &os, const tuple<Args...>& t) {
		os << get<IDX>(t) << (IDX+1 == MAX?"":",");
		PRINT_TUPLE<IDX+1, MAX, Args...>::print(os,t);
	}
};

template<int MAX, typename... Args>
struct PRINT_TUPLE<MAX, MAX, Args...> {
	static void print(ostream& os, const tuple<Args...>& t) {
	}
};

template <typename... Args>
ostream& operator<<(ostream &os, const tuple<Args...>&t) {
	os << "[";
		PRINT_TUPLE<0, sizeof...(Args), Args...>::print(os,t);
	return os << "]";
}


int main() {
	cout << make_tuple(7.5, string("hello"), bitset<16>(377), 42) << endl;
	return 0;
}
