#include <iostream>
#include <functional>
using namespace std;

void myfunc(int tv) {
    std::cout << "myfunc函数执行了,tv=" << tv << endl;
}

class TC {
public:
    void operator() (int tv) {
        std::cout << "TC::oprtator()函数执行了,tv=" << tv << endl;
    }
    void ptfunc(int tv) {
        std::cout << "TC::pfunc函数执行了,tv=" << tv << endl;
    }
    static int stcfunc(int tv) {
        std::cout << "TC::stcfunc静态成员函数执行了,tv=" << tv << endl;
        return tv;
    }
    int m_a;
};

class TC2 {
public:
    using tfpoint = void(*)(int); //定义一个函数指针类型
    static void myfunc(int tv) //静态成员函数
    {
        std::cout << "TC2::myfunc()静态成员函数执行了,tv=" << tv << endl;
    }
    operator tfpoint() {
        return myfunc;
    }
#if 0
    void operator() (int tv) {
        std::cout << "TC::oprtator()函数执行了,tv=" << tv << endl;
    }
#endif
};

class CB {
    std::function<void()> fcallback;
public:
    CB(const std::function<void()>& f): fcallback(f) {
        int i;
        i = 1;
    }
    void runcallback(void) {
        fcallback();
    }
};

class CT {
public:
    void operator() (void) {
        std::cout << "CT::oprtator()函数执行了" << endl;
    }
    void myfunc(int x, int y) //普通成员函数
    {
        cout << "x= " << x << ",y= " << y << endl;
        m_a = x;
    }
    int m_a;
    CT() {
        cout << "CT::CT()构造函数" << endl;
    }
    CT(const CT& ct) {
        cout << "CT(const CT& ct)拷贝构造函数" << endl;
    }
    ~CT() {
        cout << "CT::~CT()析构函数" << endl;
    }
};

void mycallback(int cs,const std::function<void(int)>& f) {
    f(cs);
}
void runfunc(int x) {
    cout << x << endl;
}

void myfunc1(int x, int y, int z) {
    cout << "x:= " << x << " ,y:=" << y << " ,z:=" << z << endl;
}

void myfunc2(int &x, int &y) {
    x++;
    y++;
}

int main() {
    //一:可调用对象
    //1.函数;2:重载了()运算的类的对象
    //(1.1)函数指针
    //void (*pmf)(int) = &myfunc; // 定义一个函数指针pmf并给了初值
    //pmf(15); //调用函数,这就是个可调用对象
    //(1.2)具有operator()成员函数的类对象(仿函数)
    //仿函数的定义:仿函数(functor),它的行为类似于函数的东西(something that performs a function).
    //c++仿函数是通过在类中重载()运算符实现.又称为函数对象(function object).能执行函数功能的类
    TC tc;
    tc(20); //调用的是()操作符,这也是个可调用对象,等价于tc.operator()(20);
    tc.operator()(20);
    //(1.3)可被转换为函数指针的类对象(仿函数/函数对象)
    TC2 tc2;
    tc2(50); // 先调用tfpoint,在调用myfunc,这也是个可调用对象
    tc2.operator TC2::tfpoint()(50);
    //(1.4)类成员函数指针
    void (TC::*myfpointpt)(int) = &TC::ptfunc; //类成员函数指针变量myfpointpt定义并给初值
    (tc.*myfpointpt)(80);
    //(1.5)总结
    //a)看成对象
    //b)我们可以对其使用()调用运算符,如果a是可调用对象,那么我们就可以编写a(param...)代码
    //如何能把各种不同的可调用对象的形式统一一下,统一的目的是方便咱们调用
    cout << "--------------------------------" << endl;
    //二.std::function(可调用对象包装器) c++11, std::function是个类模板,用来装各种可调用包装器
    //不能装类成员函数指针
    //std::function类模板的特点:就是能够通过
    //(2.1)绑定普通函数
    std::function<void(int)> f1 = myfunc;
    f1(100);
    //(2.2)绑定类的静态成员函数
    std::function<int(int)> fs2 = TC::stcfunc; // 绑定一个类的静态成员函数
    cout << fs2(110) << endl;
    TC tc3;
    std::function<void(int)> f3 = tc3;
    tc3(120);
    TC2 tc4;
    std::function<void(int)> f4 = tc4;
    tc4(120);
    //(2.4)小范例演示
    CT ct;  // 可调用对象
    CB cb(ct);  // cb 需要可调用对象做参数来构造,ct因为有operator()所以可以转为std::function<void(void)>&对象
    cb.runcallback(); // 执行的CT里的operator();

    for (int i = 0; i < 10; ++i) {
        mycallback(i, runfunc); // runfunc(i);
    }
    //三:std:bind绑定器,也是个类模板,c++11引入的
    //std::bind能够将对象以及相关参数绑定在一起,绑定完后可以直接调用,也可以用std::function进行保存,在需要的时候调用
    //格式
    //std::bind(待绑定的函数对象/函数指针/成员函数指针,参数绑定值1,参数绑定值2......参数绑定值n)
    //总结:
    //a)将可调用对象和参数绑定到一起,构成一个仿函数,所以可以直接调用
    //b)如果函数有做个参数,可以绑定一部分参数,其他参数在调用时候指定
    auto bf1 = std::bind(myfunc1, 10, 20, 30);  // auto表示不关心bind的返回类型,其实bind返回的是一个仿函数对象,
    //可以直接调用,也可以赋值给std::function
    bf1(); //执行myfunc1函数
    //表示绑定函数myfunc1的第三个参数为30,二myfunc1的第一个和第二个参数分别由调用bf2时的第一,二个参数指定.
    //_1是标准库定义的,占位符的含义,类似这样的占位符有20,足够我们用了
    //这里这个palceholders::_1表示这个位置,(当前placeholders::_1所在的位置)将在函数调用时,被传入的第一个参数代替
    auto bf2 = std::bind(myfunc1, std::placeholders::_1, std::placeholders::_2, 30);
    bf2(-10, -20);
    std::bind(myfunc1, std::placeholders::_1, std::placeholders::_2, 30)(5, 15); //直接调用
    auto bf3 = std::bind(myfunc1, std::placeholders::_2, std::placeholders::_1, 30);
    bf3(5, 15);  //15, 5, 30
    int a = 2;
    int b = 3;
    auto bf4 = std::bind(myfunc2, a, placeholders::_1);
    bf4(b); // 2, 4
    cout << "a = " << a << ",b= " << b << endl;
    //这说明:bind对于预先绑定的函数参数是通过值传递的,所以这个a实际上是值传递的
    //bind对于不事先绑定的参数,通过std::placeholder传递的参数,是通过引用传递的;所以b实际上是引用传递的
    //
    CT ct1; // 一个CT类对象
    auto bf5 = std::bind(&CT::myfunc, ct1, std::placeholders::_1, std::placeholders::_2); 
    bf5(10, 20);
    //上行第二个参数ct,会导致调用CT的拷贝构造函数来生成了一个CT类型的临时对象,作为std::bind的返回值
    //bind返回仿函数类型对象
    //后续的myfuncpt调用修改的是这个临时对象的m_a值,并不影响真实的ct对象m_a值
    cout << "m_a: " << ct1.m_a << endl;
    CT ct2; // 一个CT类对象
    auto bf6 = std::bind(&CT::myfunc, &ct2, std::placeholders::_1, std::placeholders::_2); 
    bf6(10, 20);
    // 上行第二个参数ct前边如果加了&,就不生成临时的CT对象了,后续myfunpt调用修改的是ct对象的m_a值
    // 这说明此时bind返回这个对象其实是ct对象本身(仿函数类型对象)
    cout << "m_a: " << ct2.m_a << endl;
    //std::bind和std::function配合使用
    CT ct3; // 一个CT类对象
    std::function<void(int, int)> bfc6 = std::bind(&CT::myfunc, &ct3, std::placeholders::_1, std::placeholders::_2);
    bf6(10, 20);
    // 把成员变量地址当作函数一样绑定,绑定的结果放在std::function<int &(void)>里面保存;
    // 说白了就是用一个可调用对象的方式来表示这个变量
    CT ct4;
    std::function<int &()> bf7 = std::bind(&CT::m_a, &ct4);
    bf7() = 60;
    // std::function<int &()> bf7 = std::bind(&CT::m_a, ct4);
    // 如果bind第二个参数用的不是&,那么这个bind会导致产生两次拷贝构造函数的执行
    // 第一次拷贝构造函数的执行是因为系统利用ct来生成一个临时的CT对象
    // 第二次拷贝构造函数的执行是因为std::bind本身要返回一个CT对象,要返回这个CT对象(仿函数)拷贝自临时的CT对象
    // 但是std::bind执行完毕后,临时CT对象会被释放,返回的这个CT对象(仿函数)就弄到bf7
    cout << "m_a: " << ct4.m_a << endl;
    return 0;
    auto rt = std::bind(CT());  //CT是构造临时对象,然后又调用了拷贝构造函数生成了一个可调用对象
    //作为std::bind的返回内容,bind返回仿函数类型对象,就是则这个拷贝构造函数构造起来的对象
    rt(); //调用的是operator()

    auto bf = std::bind(runfunc, std::placeholders::_1); // runfunc的第一个参数由调用时的第一个参数指定
    for (int i = 0; i < 10; ++i) {
        mycallback(i, bf); // 调用的是runfunc
    }
    //四:总结
    //a)bing思想所谓的延迟调用,将可调用对象统一格式,保存起来;需要的时候在调用
    //我们有用std::function绑定一个可调用对象,类成员不能绑.std::bind成员函数,成员函数等等都能绑
}
