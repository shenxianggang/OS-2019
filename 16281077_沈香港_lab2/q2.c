#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	pid_t pid;
	pid=fork();
	if(pid<0)
	{
		printf("创建子进程出错！");		
	}
	if(pid==0)
	{
		int ret;
		ret = execl("/usr/bin/vi","vi",NULL);
		if(ret==-1)
			perror("excel l error");
	} 
	if(pid>0)
	{
		printf("子进程的pid为%d\n",pid);
		printf("父进程的pid为%d\n",getpid());
		while(1)
			sleep(2);
	}
	return 0;
}
