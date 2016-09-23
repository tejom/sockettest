#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <stdio.h>

#define PORT "5000"

int main()
{
	int sockfd,err;
	struct addrinfo hints,*servinfo;
	err =0;
	printf("start\n");
	
	memset(&hints,0,sizeof hints);
	
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	char *host = "localhost";
	err = getaddrinfo(host,PORT,&hints,&servinfo);
	if(err<0){
		printf("getaddrerror\n");
		return err;
	}

	sockfd = socket(servinfo->ai_family,servinfo->ai_socktype,IPPROTO_TCP);
	if(sockfd<0){
		printf("socket error\n");
		return sockfd;
	}

	connect(sockfd,servinfo->ai_addr,servinfo->ai_addrlen);
	write(sockfd,"GET \r\n",sizeof("GET \r\n"));
	char buffer[256];
	read(sockfd,buffer,255);
	printf("%s\n",buffer);
	
	int val=1;
	socklen_t optlen = sizeof(val);
	setsockopt(sockfd,SOL_SOCKET,SO_KEEPALIVE,&val,optlen);
	char inp[256];
	fgets(inp,255,stdin);
	

	printf("in keepavlive mode\n");
	fgets(inp,255,stdin);	
	close(sockfd);
	
	printf("spcket closes\n");
	fgets(inp,255,stdin);
	printf("done\n");
	return 0;
}
