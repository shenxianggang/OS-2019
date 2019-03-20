#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
        pid_t p1,p2,p3;
        p1=fork();//
        int i=0;
        if(p1<0)
        {
                printf("我是进程%d,在创建子进程的过程中出错\n！",getpid());
        }
        if(p1==0)
{
		p2=fork();
		if(p2>0)
			p3=fork();
		pid_t p,pp;
		p=getpid();
		pp=getppid();
		while(i<100)
		{
			printf("我的进程号是%d，我的父进程号是%d\n",p,pp);
			i=i+1;
			sleep(1);
			if(p3>0 && p2>0 && i>10)
				exit(0);
		}
}
        if(p1>0)
        {
                fork();
                pid_t p,pp;
                p=getpid();
                pp=getppid();
                while(1)
        {
                        printf("我的进程号是%d，我的父进程号是%d\n",p,pp);
                        sleep(1);
        }
                sleep(1);
        }
        return 0;
}

