#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//和设置标题有关的全局量
char **g_os_argv;            //原始命令行参数数组,在main中会被赋值
char *gp_envmem = NULL;      //指向自己分配的env环境变量的内存
int  g_environlen = 0;       //环境变量所占内存大小

int main(int argc, char *const *argv)
{             

     for (int i = 0; environ[i]; i++) {
        printf("evriron[%d]地址=%x    " ,i,(unsigned int)((unsigned long)environ[i]));
        printf("evriron[%d]内容=%s\n" ,i,environ[i]);
     }
     printf("--------------------------------------------------------");

     ngx_init_setproctitle();    //把环境变量搬家
    
     for (int i = 0; environ[i]; i++) {
         printf("evriron[%d]地址=%x    " ,i,(unsigned int)((unsigned long)environ[i]));
         printf("evriron[%d]内容=%s\n" ,i,environ[i]);
     }
}
