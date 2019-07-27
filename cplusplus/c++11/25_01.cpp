#include <iostream>
#include <string.h>
#include <stdio.h>
#include <typeinfo>
#include <vector>

using namespace std;


class MyString {
public:
	static size_t DCtor; // MyString()
	static size_t Ctor;  // MyString(const char* p)
	static size_t CCtor;  // MyString(const MyString& str)
	static size_t CAsgn; // MyString& operator=(const MyString& str)
	static size_t MCtor;  // MyString(MyString&& str) noexcept
	static size_t MAsgn;  // MyStrin& operator=(const MyString&& str) noexcept
	static size_t Dtor;  // ~MyString()
	
private:
	char* _data;
	size_t _len;
	void init_data(const char *s) {
		_data = new char[_len + 1];
		memcpy(_data, s, _len);
		_data[_len] = '\0';
	}

public:
	MyString():_data(NULL),_len(0) { ++DCtor; }
	MyString(const char* p):_len(strlen(p)) {
		++Ctor;
		init_data(p);
	}
	MyString(const MyString& str):_len(str._len) {
		++CCtor;
		init_data(str._data);
	}
	MyString(MyString&& str) noexcept
	:_data(str._data),_len(str._len) {
		++MCtor;
		str._len = 0;
		str._data = NULL;
	}
	
	MyString& operator=(const MyString& str) {
		++CAsgn;
		if(this != &str) {
			if(_data) delete _data;
			_len = str._len;
			init_data(str._data);
		}
		else {
		}
		return *this;
	}
	MyString& operator=(MyString&& str) noexcept {
		++MAsgn;
		if(this != &str) {
			if(_data) delete _data;
			_data = str._data;
			_len = str._len;
			
			str._data = NULL;
			str._len = 0;		
		}
		else {
		}
		return *this;
	}
	
	~MyString() {
		++Dtor;
		if(_data) {
			delete _data;
		}
	}
	bool operator<(const MyString& rhs) const {
		return string (this->_data) < string(rhs._data);
	}
	bool operator==(const MyString& rhs) const {
		return string(this->_data) == string(rhs._data);
	}

	char* get() const {
		return _data; 
	}
};

size_t MyString::DCtor=0;
size_t MyString::Ctor=0;
size_t MyString::CCtor=0;
size_t MyString::CAsgn=0;
size_t MyString::MCtor=0;
size_t MyString::MAsgn=0;
size_t MyString::Dtor=0;


namespace std {

template<>
struct hash<MyString> {
	size_t operator() (const MyString& s) const noexcept {
		return hash<string>() (string(s.get()));
	} 
};
};


template<typename T>
void output_static_data(const T& myStr) {
	cout << typeid(myStr).name() << " --" << endl;
	cout << "CCtor=" << T::CCtor
		<< " MCtor=" << T::MCtor
		<< " CAsgn=" << T::CAsgn
		<< " MAsgn=" << T::MAsgn
		<< " Dtor=" << T::Dtor
		<< " Ctor=" << T::Ctor
		<< " DCtor=" << T::DCtor
		<< endl;
}

template<typename M, typename NM>
void test_moveable(M c1, NM c2, long& value) {
	char buf[10];
	typedef typename iterator_traits<typename M::iterator>::value_type Vltype; 
	clock_t timeStart = clock();
	for(long i=0; i<value; ++i) {
		snprintf(buf, 10, "%d", rand());
		auto ite = c1.end();
		c1.insert(ite, Vltype(buf));
	}

	cout << "construction, millo-seconds:" << (clock()-timeStart) << endl; 
	cout << "size()= " << c1.size() << endl;
	output_static_data(*(c1.begin()));

	timeStart = clock();
	M c11(c1);
	cout << "copy, millo-seconds:" << (clock()-timeStart) << endl;
	timeStart = clock();
	M c12(std::move(c1));
	cout << "move copy, millo-seconds:" << (clock()-timeStart) << endl;
	timeStart = clock();
	c11.swap(c12);
	cout << "swap, millo-seconds:" << (clock()-timeStart) << endl;
}

int main() {
	vector<MyString> vec;
	long value = 3000000;
	test_moveable(vec, vec, value);
	return 0;
}
