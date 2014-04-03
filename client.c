//server 
#include<stdio.h>
#include<string.h>
#include <errno.h>
#include<arpa/inet.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
int main(int argc,char *argv[]){
while(1)
{
int sockfd;

sockfd=socket(AF_INET,SOCK_STREAM,0);
if(sockfd<0){
perror("socket");
return -1;

}
int i;
setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&i,sizeof(int));
struct sockaddr_in addr;
memset(&addr,0,sizeof(addr));
addr.sin_family=AF_INET;
addr.sin_port=htons(5656);
inet_pton(AF_INET,argv[1],&addr.sin_addr);
if(connect(sockfd,(struct sockaddr *)&addr,sizeof(struct sockaddr_in))<0)
{
	printf("Connect error!!\n");
}
int num=send(sockfd,"SUBMITUSER:AA:",15,0);
if(num<0)
{
	printf("error");
}
//num=send(sockfd,"SUBMITDATA:AA:228:",19,0);
//printf("send%d\n",num);
sleep(10);
close(sockfd);
}
}
