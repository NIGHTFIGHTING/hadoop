

#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main(int argc, char *const *argv)
{             
    //signal(SIGHUP,SIG_IGN); //SIG_IGN标志：我要求忽略这个信号，请操作系统不要用缺省的处理方式来对待我（不要把我杀掉）；
    printf("非常高兴，大家和老师一起学习《linux c++通讯架构实战》\n");
    for(;;)
    {
         sleep(1); //休息1秒
        printf("休息1秒\n");
    }
    printf("程序退出，再见!\n");
    return 0;
}



