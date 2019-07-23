#include <iostream>
#include <time.h >
using namespace std;

class X
{
    public:
        int x;
        int y;
        int z;
        //X() :x(0), y(0), z(0)
        X()
        {
            //编译器角度 伪码；
            //vptr = vtbl; //下边的memset会把vptr（虚函数表指针）清0

            memset(this, 0, sizeof(X));
            cout << "构造函数被执行" << endl;
        }
        //X(const X &tm) :x(tm.x), y(tm.y), z(tm.z)
        X(const X &tm)
        {
            memcpy(this, &tm, sizeof(X));
            cout << "拷贝构造函数被执行" << endl;
        }
        virtual ~X()
        {
            cout << "析构函数被执行" << endl;
        }
        virtual void virfunc()
        {
            cout << "虚函数virfunc()被执行" << endl;
        }
        void ptfunc()
        {
            cout << "普通函数ptfunc()被执行" << endl;
        }
};
int main()
{   
    //第六节  单纯的类不纯时引发的虚函数调用问题
    // 单纯的类:比较简单的类，尤其不包含 虚函数和虚基类。
    //X x0;  //调用构造函数
    ///*x0.x = 100;
    //x0.y = 200;
    //x0.z = 300;*/
    //x0.virfunc(); //虚函数表指针为null居然可以成功调用虚函数；

    //X x1(x0); //调用拷贝构造函数
    //cout << "x1.x=" << x1.x << " x1.y=" << x1.y << " x1.z=" << x1.z << endl;

    //如果类并不单纯，那么在构造函数中使用如上所示的memset或者拷贝构造函数中使用如上所示的memcpy方法，那么就会出现程序崩溃的情形；
    //那就是某些情况下，编译器会往类内部增加一些我们看不见 但真实存在的成员变量（隐藏成员变量），有了这种变量的类，就不单纯了；
    //同时，这种隐藏的成员变量的 增加(使用) 或者赋值的时机，往往都是在 执行构造函数或者拷贝构造函数的函数体之前进行。
    //那么你如果使用memset,memcpy，很可能把编译器给隐藏变量的值你就给清空了，要么覆盖了；

    //比如你类中增加了虚函数，系统默认往类对象中增加 虚函数表指针，这个虚函数表指针就是隐藏的成员变量。

    //X *px0 = new X();
    //px0->ptfunc(); //正常调用
    //px0->virfunc(); //无法正常调用
    //delete px0; //无法正常调用
    //new出来的对象，虚函数变得无法正常执行了；

    //对多台，虚函数，父类子类。虚函数，主要解决的问题父类指针指向子类对象这种情况。
    //只有虚函数，没有继承，那么虚函数和普通函数有啥区别呢？ 老师认为此时就没啥时机区别。


    int i = 9;
    printf("i的地址 = %p\n", &i);
    X x0;
    printf("ptfunc()的地址=%p\n", &X::ptfunc); //打印正常的成员函数地址。
    //long *pvptrpar = (long *)(&x0);
    //long *vptrpar = (long *)(*pvptrpar);
    //printf("virfunc的地址 = %p\n", vptrpar[1]);//虚函数virfunc地址
    x0.ptfunc();
    x0.virfunc(); //不叫多态，属于静态联编
    //我们推断：这个函数ptfunc()和virfunc()函数，是在编译的就确定好的；
    //静态联编 和动态联编。
    //静态联编 ：我们编译的时候就能确定调用哪个函数。把调用语句和倍调用函数绑定到一起；
    //动态联编：是在程序运行时，根据时机情况，动态的把调用语句和被调用函数绑定到一起，动态联编一般旨有在多态和虚函数情况下才存在。

    X *pX0 = new X();
    pX0->ptfunc();
    pX0->virfunc(); //通过虚函数表指针，找虚函数表，然后从虚函数表中找到virfunc虚函数的地址并调用。

    //更明白：虚函数，多态，这种概念专门给指针或者引用用的；
    X &xy = *pX0;
    xy.virfunc();
    X &xy2 = x0;
    xy2.virfunc();


    return 1;
}


