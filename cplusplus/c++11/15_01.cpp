#include <iostream>
#include <bitset>

using namespace std;



void Print()	{
}

//û��template<typename T,typename... Types>�ػ�
template<typename... Types>
void Print(const Types&... args) {
}

template<typename T, typename ...Types>
void Print(const T& FirstArgument, const Types&... args) {
	cout << FirstArgument << endl;
	Print(args...);
}

int main() {
	Print(1,2,3,4);
	Print(7.5, "hello", bitset<16>(377), 42);
	return 0;
}
