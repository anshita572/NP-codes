#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#define SERV_TCP_PORT 5035
int main(int argc,char**argv)
{
       int sockfd;
       struct sockaddr_in serv_addr;
       struct hostent *server;
       char buffer[4096];
       sockfd=socket(AF_INET,SOCK_STREAM,0);
       serv_addr.sin_family=AF_INET;
       serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
       serv_addr.sin_port=htons(SERV_TCP_PORT);
       connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
       printf("\nEnter the message to send : ");
       fgets(buffer,4096,stdin);
       fputs(buffer,stdout);
       while(1)
       {
         if(strncmp(buffer,"quit",4)==0){
         write(sockfd,buffer,4096);
         break;
         }
         write(sockfd,buffer,4096);
         read(sockfd,buffer,4096);
         printf("\n");
         printf("\nServer message:\t%s",buffer);
         if(strncmp(buffer,"quit",4)==0){
         break;
         }
         
         printf("\nType your message:\t");
         fgets(buffer,4096,stdin);
       }
       close(sockfd);
       return(0);
}
