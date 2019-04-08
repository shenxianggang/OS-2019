#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
void pthread_yield();
int ticketCount=1000;
sem_t *mutex=NULL;
void *SaleThread(void *arg)
{
	int num,temp,i;
	num=atoi(arg);
       for(i=0;i<num;i++){
		sem_wait(mutex);
		temp=ticketCount;
		pthread_yield();//强制线程频繁切换
		temp=temp-1;
		pthread_yield();//强制线程频繁切换
		ticketCount=temp;
		sem_post(mutex);
	}
}

void *RefundThread(void *arg)
{
	int num,temp,i;
	num=atoi(arg);
	for(i=0;i<num;i++)
	{
		sem_wait(mutex);
		temp=ticketCount;
		pthread_yield();//强制线程频繁切换
		temp=temp+1;
		pthread_yield();//强制线程频繁切换
		ticketCount=temp;
		sem_post(mutex);
        }
}
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("请正确输入参数！\n");
		exit(0);
	}
	mutex=sem_open("mutex",O_CREAT,0666,1);
	printf("火车票余票初始值：%d\n",ticketCount);
	pthread_t p1,p2;
	pthread_create(&p1,NULL,SaleThread,argv[1]);
	pthread_create(&p2,NULL,RefundThread,argv[2]);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	printf("火车票余票最终值：%d\n",ticketCount);
	sem_close(mutex);
	sem_unlink("mutex");
	return 0;
}
