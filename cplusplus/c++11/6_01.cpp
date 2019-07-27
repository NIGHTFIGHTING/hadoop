#include <iostream>

using namespace std;


void print(initializer_list<int> vals);

int main() {
    int p{};
    int q;
    cout<<"p: "<<p<<" q: "<<q<<endl;
    print({12,3,5,7,11,13,17});
    print(initializer_list<int>{1,2,3,4,5});
}


void print(initializer_list<int> vals) {
	for(auto p=vals.begin(); p!=vals.end(); ++p) {
		cout<<*p<<endl;
	}
}
