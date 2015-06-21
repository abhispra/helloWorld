#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

unsigned length(Node* head)
{
	unsigned len = 0;
	Node* current = head;

	while(current != NULL)
	{
		len++;
		current = current->next;
	}
	return len;
}

int insert(Node** head, int val, unsigned pos)
{
	int err = 0;
	Node* current = NULL, *newNode = NULL;
	unsigned len = 0;

	if (head == NULL)
	{
		printf("Invalid input\n");
		goto ERR_EXIT;
	}
	
	newNode = (Node*)malloc(sizeof(Node));
	if (newNode == NULL)
	{
		printf("Failed to allocate memory\n");
		err = -1;
		goto ERR_EXIT;
	}
	
	newNode->val = val;
	current = *head;
	
	if (current == NULL)
	{
		if (pos != 0)
		{
			printf("Invalid position specified for an empty list\n");
			err = -1;
			goto ERR_EXIT;
		}
		else
		{
			*head = newNode;
			newNode->next = NULL;
		}
	}
	else if (pos == 0)
	{
		*head = newNode;
		newNode->next = current;
	}
	else
	{
		while(current != NULL && len != pos -1)
		{
			current = current->next;
			len++;
		}
		if (len == pos - 1)
		{
			newNode->next = current->next;
			current->next = newNode;
		}
		else
		{
			printf("Invalid position(%d) specified\n", pos);
			err = -1;
			goto ERR_EXIT;
		}
	}
	
ERR_EXIT:
	if (err)
	{
		free(newNode);
	}
	return err;
}

void print(Node* head)
{
	Node* current = head;
	unsigned pos = 0;
	
	while(current != NULL)
	{
		printf("Pos - %d, Val- %d\n", pos++, current->val);
		current = current->next;
	}
}

void delete(Node** head)
{
	Node* current = NULL, *ptr = NULL;
	if (head != NULL)
	{
		current = *head;
		while(current != NULL)
		{
			ptr = current->next;
			free(current);
			current = ptr;
		}
		*head = NULL;
	}
}

int deleteat(Node**head, unsigned pos, int* val)
{
	int err = 0;
	Node* current = NULL, *prev = NULL;
	unsigned len = 0;
	
	if (head == NULL)
	{
		printf("Invalid pointer input\n");
		err = -1;
		goto ERR_EXIT;
	}
	current = prev = *head;
	
	if (current == NULL)
	{
		printf("Empty list, returning\n");
		goto ERR_EXIT;
	}

	if (pos == 0)
	{
		*head = current->next;
		if (val)
			*val = current->val;
		free(current);
	}
	else
	{
		while(current->next != NULL && len != pos)
		{
			prev = current;
			current = current->next;
			len++;
		}
		if (len == pos)
		{
			prev->next = current->next;
			if (val)
				*val = current->val;
			free (current);
		}
		else
		{
			printf("Invalid position specified - %d\n", pos);
			err = -1;
			goto ERR_EXIT;
		}
	}
ERR_EXIT:
	return err;
}

int countinstance(Node* head, int val)
{
	int count = 0;
	Node* current = head;

	while(current != NULL)
	{
		if (current->val == val)
			count++;
		current = current->next;
	}
	return count;
}

int getnth(Node* head, unsigned pos)
{
	int err = -1;
	unsigned len  = 0;
	Node* current = head;
	while(current != NULL && pos != len)
	{
		current = current->next;
		len++;
	}
	if ((pos == len) && (current != NULL))
	{
		err = current->val;
	}
	else
	{
		printf("Invalid position specified\n");
	}
	return err;
}

int merge(Node**head1, Node** head2)
{
	int err = 0;
	Node* current = NULL;
	
	if (head1 == NULL || head2 == NULL)
	{
		printf("Invalid params\n");
		err = -1;
		goto ERR_EXIT;
	}

	current = *head1;
	while(current->next != NULL)
	{
		current = current->next;
	}
	current->next = *head2;
	*head2 = NULL;

ERR_EXIT:
	return err;
}

int frontbacksplit(Node** head1, Node** head2)
{
	int err = 0;
	Node* current = NULL;
	unsigned len = 0, len1 = 0, len2 = 0;
	
	if (head1 == NULL || head2 == NULL)
	{
		printf("Invalid params\n");
		err = -1;
		goto ERR_EXIT;
	}

	current = *head1;
	while(current != NULL)
	{
		len++;
		current = current->next;
	}

	if (len == 1)
	{
		printf("Length of list is 1, so cannot split\n");
		err = -1;
		goto ERR_EXIT;
	}

	len1 = len / 2; 
	if (len % 2)
	{
		len1 += 1;
	}

	current = *head1;
	while(len2 != len1 - 1)
	{
		current = current->next;
		len2++;
	}

	*head2 = current->next;
	current->next = NULL;
	
ERR_EXIT:
	return err;
}
