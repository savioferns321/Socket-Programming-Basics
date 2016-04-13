#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write



int main(int argc, char const *argv[])
{
	int mySocket, port;
	struct sockaddr_in server;
	char msg[512];

	mySocket = socket(AF_INET, SOCK_STREAM, 0);
	if(mySocket == -1){
		puts("Error while creating socket");
		return -1;
	}

	port = atoi(argv[2]);
	printf("Input server address is:  %s , and port no. is %d\n", argv[1],port);


	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	if((connect(mySocket, (struct sockaddr *)&server, sizeof(server))) < 0){
		puts("Error while connecting to server");
		return -1;
	}

	puts("Connection success");	
	
	while(scanf(" %s ", msg) != EOF){

		if(strlen(msg) == 0){
			//Exiting the connection as client has nothing more to say to the server
			puts("Closing the connection.");
			break;
		}

		if(send(mySocket, msg, strlen(msg), 0 ) < 0){
			printf(" Error while sending msg : %s\n", msg);
			perror(" Error while sending msg.");
			return -1;
		}
	}

	close(mySocket);
	
	puts("Connection closed");
	
	return 0;
}