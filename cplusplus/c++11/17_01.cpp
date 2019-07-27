#include <iostream>

using namespace std;


template<typename _ForwardIterator,
	typename _Compare>
_ForwardIterator
__max_element(_ForwardIterator __first,
	      _ForwardIterator __last,
	      _Compare __comp
		)
{
	if(__first == __last) return __first;
	_ForwardIterator __result = __first;
	while(++__first != __last) {
		if(__comp(__result, __first)) {
			__result = __first;
		}
	}
	return __result;
}

struct _Iter_less_iter
{
	template<typename _Iterator1,
         	 typename _Iterator2> 
	bool 
	operator()(_Iterator1 __it1,
		   _Iterator2 __it2)const
	{
		return *__it1 < *__it2;
	}
	
};

inline _Iter_less_iter
__iter_less_iter()
{
	return _Iter_less_iter();
}


template<typename _ForwardIterator>
inline _ForwardIterator
max_element(_ForwardIterator __first,
	    _ForwardIterator __last)
{
	return __max_element(__first, __last,
			     __iter_less_iter());
}

template<typename _Tp>
inline _Tp
max(initializer_list<_Tp> _I)
{
	return *max_element(_I.begin(),
			    _I.end());
}



int main() {
	cout << max({57, 48, 60, 100, 20 ,18}) << endl;
}
