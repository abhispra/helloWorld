#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "linkedlist.h"

int main(int argc, char* argv[])
{
	Node *head = NULL;
	unsigned i = 0, randVal = 0;
	int err = 0, val = 0;
	time_t t;

	srand((unsigned) time(&t));

	print(head);
	for (i = 0; i < LEN_MAX; i++)
	{
		randVal = rand() % LEN_MAX;
		if ((err = insert(&head, randVal, i)) != 0)
		{
			printf("insert returned err for val %d, pos %d, breaking\n", i, i);
			break;
		}
	}
	print(head);
	printf("Length of list - %d\n", length(head));
	for (i = 0; i < LEN_MAX/10; i++)
	{
		randVal = rand() % LEN_MAX;
		printf("No of instances of the value %d in the list %d\n", randVal, countinstance(head, randVal));
	}

	for (i = 0; i < LEN_MAX/10; i++)
	{
		randVal = rand() % LEN_MAX;
		printf("GetNth value for pos %d is %d\n", randVal, getnth(head, randVal));
	}

	for (i = 0; i < LEN_MAX; i++)
	{
		randVal = rand() % LEN_MAX;
		if ((err = deleteat(&head, randVal, &val)) != 0)
		{
			printf("deleteat returned error %d\n", err);
		}
		else
		{
			printf("deleteat returned value of %d for pos %d\n", val, randVal);
		}
	}
	print(head);
	printf("Length of list - %d\n", length(head));

	Node *ptr = NULL;
	err = frontbacksplit(&head, &ptr);
	printf("Length of list1 - %d\n", length(head));
	printf("List1 -->\n");
	print(head);

	printf("Length of list2 - %d\n", length(ptr));
	printf("List2 -->\n");
	print(ptr);

	if ((err = merge(&head, &ptr)) != 0)
	{
		printf("Merge retruned an error %d\n", err);
	}
	else
	{
		printf("New List after merging with length - %d\n", length(head));
		print(head);
	}
	
	if ((err = alternatesplit(&head, &ptr)) != 0)
	{
		printf("Alternatesplit returned the error %d\n", err);
	}
	else
	{
		printf("Length of list1 - %d\n", length(head));
		printf("List1 -->\n");
		print(head);

		printf("Length of list2 - %d\n", length(ptr));
		printf("List2 -->\n");
		print(ptr);
	}
	
	delete(&head);
	delete(&ptr);
	return 0;
}
