#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_THREADS 1000

Queue myQueue;
void* printThreadCount(void* arg)
{
  int err = 0;
  unsigned randVal = 0;
  int* ptr = NULL;
  time_t t;

	srand((unsigned) time(&t));
  randVal = rand() % 2;
  if (randVal || (*(int*)(arg) < MAX_THREADS/2))
	{
    ptr = malloc(sizeof(int));
    *ptr = *(int*)arg;
    err = enque(&myQueue, ptr);
    if (err)
      printf("Failed to enque %d\n", err);
  }
  else
  {
    err = dequeue(&myQueue, (void**)&ptr);
    if (err)
      printf("Failed to deque %d\n", err);
    else
    {
      printf("Dequed value %d\n", *(int*)ptr);
      free(ptr);
    }
  }
	return arg;
}

int main(int argc, char* argv[])
{
	int error = 0, index = 0;
	int *ptr = NULL;
	pthread_t threads[MAX_THREADS];

  initialize(&myQueue, NULL);
	for(index; index < MAX_THREADS; index++)
	{
		pthread_create(&threads[index], NULL, printThreadCount, &threads[index]);
	}

	for(index = 0; index < MAX_THREADS; index++)
	{
		pthread_join(threads[index], (void*)&ptr);
	}
  unsigned dep = 0;
  error = depth(&myQueue, &dep);
  if (!error)
    printf("Queue depth %d\n", dep);
  else
    printf("Error %d\n", error);
  destroy(&myQueue);

	return 0;
}
