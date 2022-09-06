#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#define MAX 80
#define PORT 2200
#define SA struct sockaddr
void func(int sockfd)
{
	char buff[MAX];
	char rbuff[4*MAX];
	int n;
	for (;;) {
		bzero(buff, sizeof(buff));
		bzero(rbuff, sizeof(rbuff));
		printf("Enter the string1: ");
		n = 0;
		//while ((buff[n++] = getchar()) != '\n')
		//	;
		scanf("%s",buff);
		write(sockfd, buff, sizeof(buff));
		printf("Enter the string2: ");
		
		bzero(buff, sizeof(buff));
		
		//while ((buff[n++] = getchar()) != '\n')
		//	;
		scanf("%s",buff);
		write(sockfd, buff, sizeof(buff));
		
		bzero(buff, sizeof(buff));
		
		read(sockfd, rbuff, sizeof(rbuff));
		printf("Concatinated strings from Server : %s\n", rbuff);
		bzero(rbuff, sizeof(rbuff));
		bzero(buff, sizeof(buff));
	}
}

int main()
{
	int sockfd, connfd;
	struct sockaddr_in servaddr, cli;

	// socket create and verification
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("socket creation failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully created..\n");
	bzero(&servaddr, sizeof(servaddr));

	// assign IP, PORT
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(PORT);

	// connect the client socket to server socket
	if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) {
		printf("connection with the server failed...\n");
		exit(0);
	}
	else
		printf("connected to the server..\n");

	// function for chat
	func(sockfd);

	// close the socket
	close(sockfd);
}

