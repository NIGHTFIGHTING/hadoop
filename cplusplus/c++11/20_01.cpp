#include <iostream>

using namespace std;

template<typename... Values> class Tuple;
template<> class Tuple<> {};



//µÝ¹é¼Ì³Ð
template<typename Head, typename... Tail>
class Tuple<Head, Tail...>
:private Tuple<Tail...>
{
	typedef Tuple<Tail...> inherited;
protected:
	Head m_head;
public:
	Tuple() {}
	Tuple(Head v,Tail... vtail):m_head(v),inherited(vtail...) {}
	//typename Head::type head() { return m_head; }
	//auto head()->decltype(m_head) { return m_head; }
	Head head() { return m_head; }
	inherited &tail() { return *this; }
};

int main() {
	Tuple<int, float, string> t(41, 6.3, "nico");

	cout << "int: " << sizeof(int) << endl;
	cout << "float: " << sizeof(float) << endl;
	cout << "char[]: " << sizeof("nico") << endl;
	cout << "size: " << sizeof(t) << endl;
	
	cout << t.head() << endl;
	cout << t.tail().head() << endl;
	cout << t.tail().tail().head() << endl;
	return 0;
}
