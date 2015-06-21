#include<signal.h>
#include<stdio.h>
#include<unistd.h>
#include<errno.h>

#define TRUE 1

void sigHandler(int signalNo)
{
	if (signalNo == SIGINT)
	{
		printf("Quietly ignoring SIGINT\n");
	}
	else if (signalNo == SIGKILL)
	{
		printf("You killed me :(\n");
	}
}

int main(int argc, char* argv[])
{
	int err = 0;

	if (signal(SIGINT, sigHandler) == SIG_ERR)
	{
		printf("Cannot register signal handler - %d\n", errno);
		return 0;
	}
   
	while(TRUE)
	{
		sleep(1);
		printf("Woke up :)\n");
	}
	return 0;
}
