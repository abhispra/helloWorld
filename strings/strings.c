#include<stdio.h>
#include<string.h>

#define BUFF_SIZE 1024

size_t mystrlen(char* buff)
{
	size_t len = 0;
	if (buff)
	{
		while(*buff++)
			len++;
	}
	return len;
}

char* mystrcpy(char* dest, char* src)
{
	char* ret_ptr = dest;

	if (dest && src)
	{
		while(*src)
		{
			*dest++ = *src++;
		}
	}
	return ret_ptr;
}

char* mystrncpy(char* dest, char* src, size_t maxlen)
{
	char* ret_ptr = dest;
	size_t len = 0;

	if (dest && src)
	{
		while(*src && len++ < maxlen)
		{
			*dest++ = *src++;
		}
	}
	return ret_ptr;
}

int main(int argc, char* argv[])
{
	int error = 0;
	size_t len = 0;
	char dest[BUFF_SIZE] = {0};
	
	if (argc != 3)
	{
		printf("Invalid usage, Usage - <string> <len>\n");
		return error;
	}
	len = atoi(argv[2]);
	mystrcpy(dest, argv[1]);
	printf("Len - %zd, Copy Normal - %s\n", mystrlen(argv[1]), dest);
	memset(dest, 0, sizeof(dest));
	mystrncpy(dest, argv[1], len);
	printf("Len - %zd, Copy strict - %s\n", mystrlen(argv[1]), dest);
	return error;
}
