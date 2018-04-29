#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

typedef struct
{
	char *data;
	int size;
} SimpleResponse;

int start(int port, int maxbuf, char *(*cb)())
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

	while (1)
	{
		connfd = accept(listenfd, (struct sockaddr *)NULL, NULL);

		recv(connfd, receiveBuff, maxbuf, 0);

		SimpleResponse res;
		res.data = (*cb)(receiveBuff);
		res.size = strlen(res.data);

		send(connfd, res.data, res.size, 0);
		close(connfd);
	}
}

// char *callback(char *buf)
// {
// 	printf("%s", buf);
// 	return "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=utf-8\r\nVary: Accept-Encoding\r\n\r\n<h1>Wow2!</h1>";
// }

// int main(int argc, char *argv[])
// {
// 	char *(*cb)() = &callback;
// 	start(5002, 1024, cb);
// 	return 0;
// };