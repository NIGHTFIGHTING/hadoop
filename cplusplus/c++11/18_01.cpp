#include <iostream>

using namespace std;

int maximum(int n) {
	return n;
}

template <typename... Args>
int maximum(int n,Args... args) {
	return max(n, maximum(args...));
}

int main() {
	cout << maximum(57, 48, 60,100, 20, 18) << endl;
}
