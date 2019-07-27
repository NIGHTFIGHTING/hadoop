#include <iostream>

using namespace std;

class P {
public:
	P(int a,int b) {
		cout << "P(int, int), a=" << a << ", b=" << b <<endl;
	}

	/*P(initializer_list<int> initlist) {
	 	cout << "P(initializer_list<int>), values= ";
		for(auto i : initlist) {
			cout << i << ' ';
		}
		cout<<endl;
	}*/
	void print(initializer_list<int> vals) {
		for(auto i=vals.begin(); i!=vals.end(); ++i) {
			cout << "value:" << *i << ' ';
		}
		cout << endl;
		for(auto i : vals) {
			cout << "auto_value:" << i << ' ';
		}
		cout <<endl;
	}
};


int main() {
	P p(77, 5);
	P q{77, 5};
	//P r{1, 2, 3};
	P s={4, 5};
    	int *value1 = new int(0);
	int *value2 = new int(2);
	initializer_list<int*> list1={value1, value2};
	initializer_list<int*> list2=list1;
	//list2=list1;
	for(auto i : list1) {
		cout << "&i:" << i << " i:" << *i << endl;
	}
	for(auto i : list1) {
		delete i;
		i = NULL;
	}
	delete &list1;
	/*for(auto i=list1.begin(); i!=list1.end(); ++i) {
		//delete *i;
		cout << *i << endl;
		//(*i) = NULL;
	}*/
	/*for(auto i : list2) {
		if(i) {
			cout << "&i:" << i << " i:"<< *i << " it is not ptrnull" <<endl;
		}
		delete i;
		i = NULL;
	}*/
	p.print({123,4545,6666,0});
	return 0;
}
