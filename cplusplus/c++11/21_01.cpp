#include <iostream>
#include <bitset>

using namespace std;

template<typename... Values> class Tuple;
template<> class Tuple<> {};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...>
{
	typedef Tuple<Tail...> composited;
protected:
	composited m_tail;
	Head m_head;
public:
	Tuple() { }
	Tuple(Head v, Tail... vtail):m_head(v),m_tail(vtail...) {}

	Head head() { return m_head; }
	composited& tail() { return m_tail; }
};

int main() {
	Tuple<string, /*complex<int>,*/ bitset<16>, double>
		it2("Ace", /*complex<int>(3, 8),*/ bitset<16>(377), 3.141592653);
	cout << sizeof(it2) << endl;
	cout << it2.head() << endl;
	cout << it2.tail().head() << endl;
	cout << it2.tail().tail().head() << endl;
	//cout << it2.tail().tail().tail().head() << endl;
	return 0;
}
