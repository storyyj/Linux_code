#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>

int main(int argc,char *argv[])
{
	int status;
	pid_t pid,wpid;
	pid=fork();
	if(pid==0)
	{
		printf("I am child,my id is %d,my father is %d\n",getpid(),getppid());
		sleep(5);
		printf("I go to die\n");
		return 66;
	}
	else if(pid>0)
	{
		wpid=wait(&status);
		if(wpid==-1)
		{
			perror("wait error");
			exit(1);
		}
		if(WIFEXITED(status))
		{
			printf("My child exit %d\n",WEXITSTATUS(status));
		}
		if(WIFSIGNALED(status))
		{
			printf("My child was killed %d\n",WTERMSIG(status));
		}
		printf("I have finished wait my child\n");
	}
	else
	{
		perror("fork error");
		return 1;
	}
	return 0;
}
