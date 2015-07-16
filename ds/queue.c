#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include "queue.h"

void lock(pthread_mutex_t* mutex)
{
  int err = 0;
  if ((err = pthread_mutex_lock(mutex)) != 0)
  {
    printf("Failed to aquire globbal lock %d\n", err);
    abort();
  }
}

void unlock(pthread_mutex_t* mutex)
{
  int err = 0;
  if ((err = pthread_mutex_unlock(mutex)) != 0)
  {
    printf("Failed to aquire globbal lock %d\n", err);
    abort();
  }
}

int initialize(Queue *myQueue, myFree_cb myFree)
{
  int err = 0;
  //More initialization may be added later
  if (myQueue == NULL)
  {
    err = ERR_INVALID_PARAM;
    printf("Invalid param passed %d\n", err);
    goto ERR_EXIT;
  }

  memset(myQueue, 0, sizeof(Queue));
  if ((err = pthread_mutex_init(&(myQueue->mutex), NULL)) != 0)
  {
    printf("Failed to initialize global mutex %d\n", err);
    goto ERR_EXIT;
  }

  lock(&(myQueue->mutex));
  if (myFree)
  {
    myQueue->func = myFree;
  }
  else
  {
      myQueue->func = free;
  }
  unlock(&(myQueue->mutex));

ERR_EXIT:
  return err;
}

int enque(Queue* myQueue, void* data)
{
  int err = 0;
  Node* newNode = (Node*)malloc(sizeof(Node));
  if (newNode == NULL)
  {
    err = ERR_NO_MEM;
    printf("Out of memory %d\n", err);
    goto ERR_EXIT;
  }
  newNode->data = data;
  newNode->next = NULL;

  lock(&(myQueue->mutex));
  if (myQueue->tail)
  {
    myQueue->tail->next = newNode;
    myQueue->tail = newNode;
  }
  else
  {
    myQueue->tail = myQueue->head = newNode;
  }
  myQueue->depth++;
  unlock(&(myQueue->mutex));

ERR_EXIT:
  return err;
}

int dequeue(Queue* myQueue, void** data)
{
  int err = 0;
  Node* ptr = NULL;

  lock(&(myQueue->mutex));
  if (myQueue->depth == 0)
  {
    unlock(&(myQueue->mutex));
    err = ERR_QUEUE_UNDEFLOW;
    printf("Queue underflow %d\n", err);
    goto ERR_EXIT;
  }

  *data = myQueue->head->data;
  ptr = myQueue->head;

  myQueue->head = myQueue->head->next;
  myQueue->depth--;
  free(ptr);
  if (myQueue->depth == 0)
  {
    myQueue->head = myQueue->tail = NULL;
  }
  unlock(&(myQueue->mutex));

ERR_EXIT:
  return err;
}

void destroy(Queue* myQueue)
{
  int err = 0;

  lock(&(myQueue->mutex));
  Node* ptr = myQueue->head, *prevptr = ptr;
  while(ptr != NULL)
  {
    ptr = ptr->next;
    myQueue->func(prevptr->data);
    free(prevptr);
    prevptr = ptr;
  }
  memset(myQueue, 0, sizeof(Queue));
  unlock(&(myQueue->mutex));

ERR_EXIT:
  return;
}

int depth(Queue* myQueue, unsigned* depth)
{
  *depth = 0;
  int err = 0;

  lock(&(myQueue->mutex));
  *depth = myQueue->depth;
  unlock(&(myQueue->mutex));

ERR_EXIT:
    return err;
}
