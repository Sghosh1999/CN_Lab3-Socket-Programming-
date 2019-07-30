#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

void main(int argc, char *argv[])
  {
    char *ab = argv[1];
    int port_no = atoi(ab);
    
    //SOCKET
	int a =socket(AF_INET,SOCK_DGRAM,0);
	if(a==-1)
	{
		printf("\nSocket ERROR");
	}

    //BIND
	struct sockaddr_in Server;
	Server.sin_family=AF_INET;
	Server.sin_port=htons(port_no);
	Server.sin_addr.s_addr=inet_addr("127.0.0.1");
	int b=bind(a,(const struct sockaddr *)(&Server),sizeof(Server));
	if(b==-1)
	{
		printf("\nBind ERROR");
	}

   while(1)
	{
		//RECEIVEFROM
		char str[100];
		struct sockaddr_in Client;
		Client.sin_family=AF_INET;
		Client.sin_port=htons(5500);
		Client.sin_addr.s_addr=inet_addr("127.0.0.1");
		recvfrom(a,str,sizeof(str),0,(struct sockaddr *)(&Client),(int *)sizeof(Client));
		printf("\nReceived from Client:%s",str);

		char str1[100];
		printf("\nEnter Message to Send (MAX 100) (Type X to Close):");
		scanf("%s",str1);
              
		if(strcmp(str1,"X")==0)
		{
			break;
		}

		//SENDTO
		sendto(a,str1,strlen(str1),0,(const struct sockaddr *)(&Client),sizeof(Client));
	}

	//CLOSE
	close(a);
    

   }
