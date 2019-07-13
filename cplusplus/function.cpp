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
};

void mycallback(int cs,const std::function<void(int)>& f) {
    f(cs);
}
void runfunc(int x) {
    cout << x << endl;
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
    //三:std:bing绑定器,也是个类模板,c++11引入的
    //std::binf能够将对象以及相关参数绑定在一起,绑定完后可以直接调用,也可以用std::function进行保存,在需要的时候调用
    //格式
    //std::bind(待绑定的函数对象/函数指针/成员函数指针,参数绑定值1,参数绑定值2......参数绑定值n)
    //总结:
    //a)将可调用对象和参数绑定到奇异,构成一个仿函数,所以可以直接调用
    return 0;
}
