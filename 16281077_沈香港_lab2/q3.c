#include<stdio.h>
#include<unistd.h>
int main()
{
        pid_t p1,p2;
        p1=fork();//
        if(p1<0)
        {
                printf("我是进程%d,在创建子进程的过程中出错\n！",getpid());      
        }
        if(p1==0)
        {
                p2=fork();
                if(p2>0)
                        fork();
                pid_t p,pp;
                p=getpid();
                pp=getppid();//给变量赋值主要是为了调试方便
                printf("我的进程号是%d，我的父进程号是%d\n",p,pp);
                sleep(1);


        }
        if(p1>0)
        {
                fork();
                pid_t p,pp;
                p=getpid();
                pp=getppid();
                printf("我的进程号是%d，我的父进程号是%d\n",p,pp);
                sleep(1);
        }
        return 0;
}
