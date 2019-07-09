#include <iostream>
#include <memory>
using namespace std;

//void myfunc(shared_ptr<int> ptmp) {
shared_ptr<int> myfunc(shared_ptr<int> ptmp) {
    return ptmp;
}

// 如果参数为引用,则只能指针的引用计数不会增加
shared_ptr<int> myfunc_reference(shared_ptr<int>& ptmp) {
}

// 我们的删除器,删除征信指针用的,当只能指针引用计数为0,就会自动调用该删除器来删除对象
void myDelete(int* p) {
    // 写一些日志
    delete p;  // 既然你自己提供了删除器来取代只能指针的缺省删除器,你就有义务自己来删除所指向的对象(引用技术为0时)
}

class A {
public:
    A() {
    }
    ~A() {
    }
};

//写个函数模板来封装shared_ptr数组
template<typename T>
shared_ptr<T> make_shared_array(size_t size) {
    return shared_ptr<T>(new T[size], default_delete<T[]>());
}
int main() {
    //一.shared_ptr引用技术的增加和减少
    //共享式,引用计数,每一个shared_ptr的拷贝都指向相同的内存(对象),只有最后一个指向该对象的
    //(1.1)引用技术的增加
    //shared_ptr指针不需要在指向该对象的时候,这个shared_ptr才会去析构所指向的对象
    //auto p6 = make_shared<int>(100); // 目前p6所指向的对象只有p6一个引用者;
    //auto p7(p6);// 智能指针定义时的初始化,p7和p6指向了相同的对象,此对象目前有两个引用者

    //在如下情况下,所有指向这个对象的shared_ptr引用技术都会增加1;
    //a)向上边这样,我们用p6来初始化p7这个智能指针;
    //b)把智能指针当做实参往函数里传递;
    //myfunc(p7);
    //c)作为函数的返回值
    //auto p8 = myfunc(p7); // 引用技术会变成3.这是因为有p8来接这个临时的智能指针
    //myfunc(p7); // 没有变量来接这个临时的只能指针,则临时智能指针生命周期到了,引用计数从3恢复到2

    //(1.2)引用技术的减少
    //a)给shared_ptr赋予新值,让该shared_ptr指向一个新对象;
    //p8 = make_shared<int>(200); // p8指向新对象,计数为1,p6,p7指向的对象计数恢复为2;
    //p7 = make_shared<int>(300); // p7指向新对象,计数为1,p6指向的对象计数恢复为1;
    //p6 = make_shared<int>(400); // p6指向新对象,数为1,p6指向的原内存被释放;
    //b)局部的shared_ptr离开其作用域
    //auto p6 = make_shared<int>(100); // 目前p6所指向的对象只有p6一个引用者;
    //auto p7(p6); // p7和p6指向了相同的对象,引用计数为2
    //void myfunc(shared_ptr<int> ptmp) {
    //}
    //myfunc(p7); // 进入函数体myfunc中是3个引用技术,从myfunc中退出是引用计数恢复为2个
    //c)当一个shared_ptr引用技术从1变为0,则它会自动释放自己所管理(指向)的对象
    //auto p9 = make_shared<int>(100); // 只有p9指向该对象
    //auto p10 = make_shared<int>(100);
    //p9 = p10; // 给p9复制会让p9指向p10所指向的对象,该对象引用计数变成2,而原来的p9所指向
    //的对象引用技术会从1变为0,从而导致被释放
    
    //二.shared_ptr指针常用操作
    //(2.1)use_count();返回多少个只能指针指向某个对象,主要用于调试目的
    //shared_ptr<int> myp(new int(100));
    //int icount = myp.use_count(); // 1
    //shared_ptr<int> myp2(myp);
    //icount = myp.use_count(); // 2
    //shared_ptr<int> myp3;
    //myp3 = myp2;
    //icount = myp3.use_count(); // 3
    //icount = myp.use_count(); // 3

    //(2.2)unique():是否该只能指针独占某个指向的对象(不能为空),也就是若只有一个智能指针指向某个对象
    //则unique()返回true,否则返回false
    //shared_ptr<int> myp(new int(100));
    //shared_ptr<int> myp2(myp);
    //if (myp.unque()) { 
    //    cout << " unique OK" << endl;
    //} else {
    //    cout << " unique No" << endl;
    //}
    //(2.3)reset:恢复(复位/重置)的意思
    //a)reset()不带参数时
    //若pi是唯一指向该对象的指针,那么释放pi所指向的对象,并将pi置空
    //shared_ptr<int> pi(new int(100));
    //pi.reset();
    //if (pi == nullptr) {
    //    cout << "pi is nullptr" << endl;
    //}
    //若pi不是唯一指向该对象的指针,那么不释放pi所指向的对象,但指向该对象的引用技术会减少1,同时pi置空
    //shared_ptr<int> pi(new int(100));
    //auto pi2(pi);
    //cout << pi.use_count() << endl;
    //pi.reset();
    //if (pi == nullptr) {
    //    //cout << "pi is nullptr" << endl;
    //}
    //cout << pi.use_count() << endl;
    //cout << pi2.use_count() << endl;
    //b)reset带参数,(一般是一个new出来的指针)时
    //若pi是唯一指向该对象的指针,则释放pi所指向的对象,让pi指向新对象
    //若pi不是唯一指向该对象的指针,则不释放pi所指向的对象,但指向该对象的引用计数会减少1,同时pi指向新对象
    //shared_ptr<int> pi(new int(100));
    //auto pi2(pi); // pi2引用计数会变成2
    //pi.reset(new int(1));    // 释放原内存,指向新内存
    //if (pi.unique()) {
    //    cout << "pi unique OK" << endl;
    //}
    //if (pi2.unique()) {
    //    cout << "pi2 unique OK" << endl;
    //}
    //空指针也可以通过reset来重新初始化
    //shared_ptr<int> p;
    //p.reset(new int(1)); //释放p所指向的对象,让p指向新对象,因为原来p为空,所以就等于啥也没释放直接指向新对象
    
    //(2.4)*解引用:获得p指向的对象
    //shared_ptr<int> pother(new int (123456));
    //cout << *pother << endl;
    //
    //(2.5) get():考虑到有些函数(第三方函数)的参数需要的是一个内置裸指针而不是智能指针
    //p.get():返回p中保存的指针(裸指针),小心使用,如果只能指针释放了所指向的对象,
    //那么这个返回的裸指针也就变得无效了
    //shared_ptr<int> myp(new int(100));
    //int* p = myp.get();
    //*p = 45;
    //delete p;千万不要这么干,不然系统报告异常,产生不可预料的结果
    //
    //(2,6)swap():交换两个智能指针所指向的对象
    //shared_ptr<string> ps1(new string("I Love China1"));
    //shared_ptr<string> ps2(new string("I Love China2"));
    //std::swap(ps1, ps2);
    //ps1.swap(ps2);
    //
    //(2.7) = nullptr
    //a)将所指向的对象,引用技术减1,若引用技术变为0,则释放智能指针所指向的对象
    //b)将智能指针置为空
    //shared_ptr<string> ps1(new string("I Love China"));
    //shared_ptr<string> ps2(ps1);
    //ps1 = nullptr;
    //
    //(2.8)智能指针名字作为判断条件
    //shared_ptr<string> ps1(new string("I Love China"));
    //ps1 = nullptr;
    //if (!ps1) {
    //    cout << "ps1 is nullptr" << endl;
    //}
    //
    //(2.9)指定删除器以及数组问题
    //a)指定删除器
    //一定时机帮我们删除所指向的对象; delete:将delete运算符号作为默认的资源析构方式。
    //我们可以指定自己的删除器取代系统提供的默认删除器,当智能指针需要删除所指向的对象时,编译器就会调用我们自己
    //提供的删除器来删除
    //shared_ptr指定删除器方法比较简单,一般只需要在参数添加具体的删除器函数名即可
    //shared_ptr<int> p(new int(123456), myDelete);
    //shared_ptr<int> p2(p); // 两个引用计数
    //p2.reset();  // 剩1个引用技术,po2为nullptr
    //p.reset();  // 因为此时只有1个引用技术,所以要释放指向的对象,调用我们的删除器myDelete,同时p置空
    //
    //删除器可以是一个lambda表达式
    //shared_ptr<int> p(new int(123456), [](int* p) {
    //    delete p;
    //});
    //有些情况,默认删除器处理不了(用shared_ptr管理动态数组),需要我们提供自己指定的删除器
    //shared_ptr<int> p(new int[10], []int(*p) {
    //    delete []p;
    //});
    //shared_ptr<A> pA(new A[10]);
    //shared_ptr<A> pA(new A[10], [](A *p) {
    //    delete []p;
    //});异常因为系统释放pA是deelete pA所指向的裸指针,而不是delete []pA,这种情况下我们需要写自己的删除器
    //
    //可用default_delete来做删除器,default_delete是标准库里的模板类。
    //shared_ptr<A> pA(new A[10], std::default_delete<A[]>());
    //A a;
    //pA[0] = &a;错误
    //定义数字的时候我们在尖括号中加[]
    //shared_ptr<A[]> pA(new A[10]);  // 在<>中加上[]就行了
    //shared_ptr<int[]> p(new int[10]);
    //p[0] = 12;
    //p[1] = 15;
    shared_ptr<int> pintArr= make_shared_array<int>(5);
    shared_ptr<A> pAArr= make_shared_array<A>(15);

    //b)指定删除器额外说明
    //就算是两个shared_ptr指定了不同的删除器,只要他们所指向对象的类型相同,那么这两个shared_ptr也属于同一个类型
    //
    //auto lambda1 = [](int *p) {
    //  // 日志
    //  delete p;
    //}
    //auto lambda1 = [](int *p) {
    //  // 日志
    //  delete p;
    //}
    //shared_ptr<int> p1(new int(100), lambda1);
    //shared_ptr<int> p2(new int(200), lambda2);
    //p2 = p1;  // p2会调用lambda2把自己所指向的对象释放,然后指向p1所指向的对象,p1所指向的对象引用计数为2
    //整个main执行完毕后,还会调用lambda1来释放p1和p2共同指向的对象
    //类型相同,就代表可以放到元素类型为该对象类型的容器里来
    //vector<shared_ptr<int>> pvec{p1, p2};
    //
    //make_shared是提倡的生成shared_ptr的方法,但是make_shared这种方法,让我们没有办法制定自己的删除器
}
