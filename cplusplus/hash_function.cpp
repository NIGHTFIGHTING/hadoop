//40.一个万用的hash function
#include <iostream>
#include <functional>
#include <unordered_set>
#include<functional>

using namespace std;


// 一个万用的Hash Function 如下：
template<typename T>
inline void hash_combine(size_t &seed, const T& val) {
    seed ^= std::hash<T>()(val) + 0x9e3779b9 + (seed << 6) + (seed >> 2);  //0x9e3779b9
}
//auxiliary generic functions
template<typename T>
inline void hash_val(size_t &seed, const T & val) {
    hash_combine(seed, val);
}

    template<typename T,typename... Types>
inline void hash_val(size_t & seed, const T& val, const Types &...args) //逐一取val改变seed（pass by reference）
{
    hash_combine(seed, val);
    hash_val(seed, args...);
}
//auxiliary generic function
    template<typename... Types>
inline size_t hash_val(const Types&... args) //seed最终就被视为hash code
{
    size_t seed = 0;
    hash_val(seed, args...);
    return seed;
}


// hash函数为了打乱
class Customer {
public:
    Customer(const string& fname1, const string& lname1, long int no1):fname(fname1),lname(lname1),no(no1) {
    }
    string fname;
    string lname;
    long int no;

    bool operator==(const Customer& customer)const{
        return fname == customer.fname;
    }
};

//第一种
class CustomerHash {
public:
    size_t operator()(const Customer& c) const {
        return hash_val(c.fname, c.lname, c.no);
    }
};

//第二种
size_t customer_hash_func(const Customer& c) {
    return hash_val(c.fname, c.lname, c.no);
}

//第三种,以struct hash偏特化形式实现Hash Function
namespace std {
template<>
struct hash<Customer> {
    size_t operator()(const Customer& c) const noexcept {
        cout << "+++" << endl;
        return hash_val(c.fname, c.lname, c.no);
    }
};
}

int main() {
    //unordered_set<Customer, CustomerHash> set3;
    unordered_set<Customer> set3;
    unordered_set<Customer, size_t (*)(const Customer&)> custset(20, customer_hash_func);
    set3.insert(Customer("Ace", "Hou", 1L));
    set3.insert(Customer("Sabri", "Hou", 2L));
    cout << "set3 current bucket_count: " << set3.bucket_count() << endl;
    // 打印每个bucket的元素个数
    for (unsigned i = 0; i < set3.bucket_count(); ++i) {
        cout << "bucket #" << i << " has " << set3.bucket_size(i) << " elements.\n";
    }
    CustomerHash hh;
    cout << "hash_code: " <<  hh(Customer("Ace", "Hou" , 1L)) << endl;
    // 判断这个元素在那个bucket中
    cout << hh(Customer("Ace", "Hou" , 1L)) % set3.bucket_count() << endl;
}
