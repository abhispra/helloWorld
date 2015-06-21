#ifndef __LINKED__LIST__HEADER__
#define __LINKED__LIST__HEADER__

#define LEN_MAX    100

typedef struct node {
	struct node* next;
	int val;
}Node;

unsigned length(Node* head);
int insert(Node** head, int val, unsigned pos);
void print(Node* head);
void delete(Node** head);
int deleteat(Node**head, unsigned pos, int* val);
int countinstance(Node* head, int val);
int getnth(Node* head, unsigned pos);

#endif //__LINKED__LIST__HEADER__
