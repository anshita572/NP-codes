#include <stdio.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#define MAX 80
#define PORT 2200
#define SA struct sockaddr

void func(int connfd)
{
	char buff1[4*MAX];
	char buff2[MAX];
	int n;
	for (;;) {
		bzero(buff1, sizeof(buff1));
		bzero(buff2, sizeof(buff2));

		// read the message1 from client and copy it in buffer
		read(connfd, buff1, sizeof(buff1));
		printf("String1:%s\n",buff1);
		// read the message2 from client and copy it in buffer
		read(connfd,buff2,sizeof(buff2));
		printf("String2:%s\n",buff2);
		strcat(strcat(buff1," "),buff2);
		printf("Sending To Client %s\n",buff1);
		// print buffer which contains the client contents
		// and send that buffer to client
		write(connfd, buff1, sizeof(buff1));
		bzero(buff1, sizeof(buff1));
		bzero(buff2, sizeof(buff2));
	}
}

int main()
{
	int sockfd, connfd, len;
	struct sockaddr_in servaddr, cli;
	
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
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);
	// Binding newly created socket to given IP and verification
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
		printf("socket bind failed...\n");
		exit(0);
	}
	else
		printf("Socket successfully binded..\n");

	// Now server is ready to listen and verification
	if ((listen(sockfd, 5)) != 0) {
		printf("Listen failed...\n");
		exit(0);
	}
	else
		printf("Server listening..\n");
	len = sizeof(cli);

	// Accept the data packet from client and verification
	connfd = accept(sockfd, (SA*)&cli, &len);
	if (connfd < 0) {
		printf("server accept failed...\n");
		exit(0);
	}
	else
		printf("server accept the client...\n");

	// Function for chatting between client and server
	func(connfd);

	// After chatting close the socket
	close(sockfd);
}
