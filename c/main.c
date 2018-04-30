#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void start_server(int port, int maxbuf, char *(*cb)(), void (*on_start)())
{
	int listenfd = 0;
	int connfd = 0;
	struct sockaddr_in serv_addr;

	char sendBuff[maxbuf];
	char receiveBuff[maxbuf];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(port);

	bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

	listen(listenfd, 10);

	// client cb
	(*on_start)();

	while (1)
	{
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		// read client req into buffer
		recv(connfd, receiveBuff, maxbuf, 0);

		// calc res
		char *res = (*cb)(receiveBuff);

		// read res buffer to client
		send(connfd, res, strlen(res), 0);
		close(connfd);
		free(res);
	}
}
