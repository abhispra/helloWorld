#ifndef __QUEUE__IMPL__
#define __QUEUE__IMPL__

#include <pthread.h>

#define ERR_NO_MEM            -1000
#define ERR_QUEUE_UNDEFLOW    -1001
#define ERR_INVALID_PARAM     -1002

typedef void (*myFree_cb)(void*);

typedef struct node {
  void* data;
  struct node* next;
}Node;

typedef struct queue {
  int depth;
  Node* head;
  Node* tail;
  pthread_mutex_t mutex;
  myFree_cb func;
}Queue;

int initialize(Queue *myQueue, myFree_cb myFree);
int enque(Queue* myQueue, void* data);
int dequeue(Queue* myQueue, void** data);
int depth(Queue* myQueue, unsigned* depth);
void destroy(Queue* myQueue);
#endif
