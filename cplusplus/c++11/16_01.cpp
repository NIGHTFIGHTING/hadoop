#include <iostream>
#include <exception>
#include <cmath>

using namespace std;



//% 和 值 不对等
void Printf(const char *s) {
	while(*s) {
		if(*s == '%' && *(++s) != '%') {
			//throw std::runtime_error("invalid format string: missing arguments");
		}
		cout<< *s++;
	}
}

template<typename T,typename ...Types>
void Printf(const char *s, T value,const Types&... args) {
	while(*s) {
		if(*s == '%' && *(++s) != '%') {
			cout << value ;
			Printf(++s, args...);
			return;
		}
		cout<<*s++;
	}	
	//throw std::logic_error("extra arguments provided to prinf");
}
int main() {
	int *pi = new int;
	Printf("%d %d %p %f \n",
		15,
		"This is Ace",
		pi,
		3.141592653);
	return 0;
}
