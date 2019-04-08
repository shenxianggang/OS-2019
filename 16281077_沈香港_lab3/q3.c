#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<semaphore.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
char buf[10];
sem_t *empty=NULL;//缓存区未写入数量
sem_t *full=NULL;//缓存区写入数量
void *producer(void *arg)
{
	
	for(int i=0;i<10;i++)
	{
		sem_wait(empty);
		scanf("%c",&buf[i]);
		sem_post(full);
		if(i==9)
		{
			i=-1;
		}
	}	
}
void *comsumer(void *arg)
{
	for(int i=0;i<10;i++)
	{
		sem_wait(full);
		printf("输出：%c\n",buf[i]);
		sem_post(empty);
		sleep(1);
		if(i==9)
		{
			i=-1;		
		}
	}	
}

int main(int argc,char *argv[])
{
	empty=sem_open("_empty",O_CREAT,0666,10);
	full=sem_open("_full",O_CREAT,0666,0);
	pthread_t p1,p2;
	pthread_create(&p1,NULL,producer,NULL);
	pthread_create(&p2,NULL,comsumer,NULL);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	sem_close(empty);
	sem_close(full);
	sem_unlink("_empty");
	sem_unlink("_full");
	return 0;
}
