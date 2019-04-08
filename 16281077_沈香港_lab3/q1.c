#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<fcntl.h>
int main()
{
	sem_t *P1_signal,*P2_signal,*P3_signal;
	P1_signal=sem_open("P1_signal",O_CREAT,0666,0);
	P2_signal=sem_open("P2_signal",O_CREAT,0666,0);
	P3_signal=sem_open("P3_signal",O_CREAT,0666,0);
        pid_t p2,p3,p4;//主函数的进程为P1
	p2=fork();//创建进程P2
	if(p2<0)	
	{
		perror("创建进程p2出错\n");
	}
	if(p2==0)//当前运行进程为p2
	{
		sem_wait(P1_signal);
		printf("I am the process P2\n");
		sem_post(P1_signal);
		sem_post(P2_signal);//p4进程条件
	}
	if(p2>0)//当前运行进程为P1
	{
		p3=fork();//创建进程p3
		if(p3<0)	
		{
			perror("创建进程p出错！");
		}
		if(p3==0)//当前运行进程为P3
		{
			sem_wait(P1_signal);
			printf("I am the process P3\n");
			sem_post(P1_signal);
			sem_post(P3_signal);//P4进程条件
		}
		if(p3>0)//当前运行进程为P1
		{
			printf("I am the process P1\n");
			sem_post(P1_signal);
			p4=fork();//创建进程P4
			if(p4<0)	
			{
				perror("创建进程p4出错\n");
			}
			if(p4==0)
			{
				sem_wait(P2_signal);
				sem_wait(P3_signal);
				printf("I am the process P4\n");
				sem_post(P2_signal);
				sem_post(P3_signal);
			}
		}
	}
	sem_close(P1_signal);
	sem_close(P2_signal);
	sem_close(P3_signal);
	sem_unlink("P1_signal");
	sem_unlink("P2_signal");
	sem_unlink("P3_signal");
	return 0;
}
