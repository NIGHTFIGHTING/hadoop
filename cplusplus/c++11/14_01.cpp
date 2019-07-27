#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

auto I = []()mutable -> void{
	cout << "hello world" << endl;
};

/*int id = 0 ;

auto f = [id]()mutable {
	cout << "id: " << id << endl;
	++id;
};*/

//id = 42;


class LambdaFunctor {
public:
	LambdaFunctor(int a, int b):m_a(a),m_b(b) {}
	bool operator()(int n) const {
		return m_a < n && n < m_b;
	}
private:
	int m_a;
	int m_b;
};


int main() {
	I();
	int id = 0 ;
	auto f = [id](int param) mutable {
		cout << "id: " << id << " param: "<< param << endl;
		++id;
		++param;
	};
	id = 42;
	f(7);
	f(7);
	f(7);

	
	vector<int> vi {5, 28, 50,83, 70, 590, 245, 59, 24};
	int x = 30;
	int y = 100;
	vi.erase(remove_if(vi.begin(),
			   vi.end(),
			   [x,y](int n){ return x<n&&n<y; }
			  ),
		vi.end()
		);
	
 	vi.erase(remove_if(vi.begin(), vi.end(),LambdaFunctor(x,y)),
		vi.end());
 	
	for(auto i : vi) {	
		cout << "i: " << i << ' ' ;
	}

	cout << endl;
	return 0;
}
