#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

typedef struct clientData {
	struct sockaddr_in cli_addr;
	int clientFD;
}clientData;

void* DoWork(void* arg)
{
	clientData* data = (clientData*)arg;
	
}

int main(int argc, char* argv[])
{
	int err = 0, socketfd = -1, acceptedfd = -1;
	unsigned port = 4000;
	struct sockaddr_in ser_addr, cli_addr;
	clientData* data = NULL;
	
	if (argc >= 2)
	{
		port = atoi(argv[1]);
	}

	socketfd = socket(AF_INET, SOCK_STREAM, 0);
	if (socketfd == -1)
	{
		printf("Failed to create socket %d\n", errno);
		goto ERR_EXIT;
	}

	memset(ser_addr, 0, sizeof(ser_addr));
	memset(cli_addr, 0, sizeof(cli_addr));

	ser_addr.sin_family = AF_INET;
	ser_addr.sin_addr.s_addr = INADDR_ANY;
	ser_addr.sin_port = port;

	if (bind(socketfd, &ser_addr, sizeof(ser_addr)) != 0)
	{
		printf("Unable to bind, error - %d\n", errno);
		goto ERR_EXIT;
	}

    while (1)
	{
		
		if (listen(socketfd, 10) == -1)
		{
			printf("Failed in listen call, error - %d\n", errno);
			goto ERR_EXIT;
		}

		if ((acceptedfd = accept(socketfd, cli_addr, sizeof(cli_addr))) == -1)
		{
			printf("Failed in listen call, error - %d\n", errno);
			goto ERR_EXIT;
		}

		pthread_t thread;
		pthread_attr_t attr;

		if ((err = pthread_attr_init(&attr)) != 0)
		{
			printf("Failed to initialize pthread attr %d\n", err);
			goto ERR_EXIT;
		}

		if ((err = pthread_set_detachstate(&attr, PTHREAD_CRAETE_DETACHED)) != 0)
		{
			printf("Failed to set detached state %d\n", err);
			goto ERR_EXIT;
		}
		data = (clientData*)malloc(sizeof(clientData));
		memcpy(data->cli_addr, cli_addr, sizeof(cli_addr));
		data->clientFD = acceptedfd;

		if ((err = pthread_create(&thread, &attr, DoWorrk, data)) != 0)
		{
  			printf("Failed to create new thread %d\n", err);
			goto ERR_EXIT;
   		}
	}
	
}
