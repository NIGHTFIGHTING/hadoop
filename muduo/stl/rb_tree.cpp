#include <set>
#include <iostream>
using namespace std;

//容器rb_tree
//                    key和data合成value(key|value)
//template<class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
//class rb_tree {
//protected:
//    typedef __rb_tree_node<Value> rb_tree_node;
//    ...
//public:
//    typedef rb_tree_node* link_type;
//protected:
//    //RB-tree只以三笔表现他自己
//    size_type node_count; // rb_tree的大小(节点)
//    link_type header;
//    Compare key_compare; //key的大小比较规则,应会是个function object
//};
namespace jj31
{
    void test_Rb_tree()
    {
        //G2.9 vs. G4.9 : 
        //rb_tree => _Rb_tree, 
        //identity<> => _Identity<>
        //insert_unique() => _M_insert_unique()
        //insert_equal() => _M_insert_equal()

        cout << "\ntest_Rb_tree().......... \n";

        _Rb_tree<int, int, _Identity<int>, less<int> > itree;
        cout << itree.empty() << endl;  //1
        cout << itree.size() << endl;   //0

        itree._M_insert_unique(3);
        itree._M_insert_unique(8);
        itree._M_insert_unique(5);
        itree._M_insert_unique(9);
        itree._M_insert_unique(13);
        itree._M_insert_unique(5);  //no effect, since using insert_unique().
        cout << itree.empty() << endl;  //0
        cout << itree.size() << endl;   //5
        cout << itree.count(5) << endl; //1

        itree._M_insert_equal(5);
        itree._M_insert_equal(5);
        cout << itree.size() << endl;   //7, since using insert_equal().
        cout << itree.count(5) << endl; //3       
    }                                                            
}
int main() {
    jj31::test_Rb_tree();
    return 0;
}
