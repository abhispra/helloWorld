#include <stdio.h>
#include <pthread.h>

#define MAX_THREADS 20

void* printThreadCount(void* arg)
{
	printf("%d\n", *(int*)arg);
	return arg;
}

int main(int argc, char* argv[])
{
	int error = 0, index = 0;
	int *ptr = NULL;
	pthread_t threads[MAX_THREADS];

	for(index; index < MAX_THREADS; index++)
	{
		pthread_create(&threads[index], NULL, printThreadCount, &threads[index]);
	}

	for(index = 0; index < MAX_THREADS; index++)
	{
		pthread_join(threads[index], (void*)&ptr);
		printf("Return from thread %d - %d\n", index, *(int*)ptr);
	}
	return 0;
}
