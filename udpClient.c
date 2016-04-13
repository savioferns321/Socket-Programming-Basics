#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <time.h>

int main(int argc, char const *argv[])
{
	int mySocket, port, serverSize, sendLen, buffersize = atoi(argv[3]);
	unsigned long long time_diff;
	float throughput;
	struct timeval start_time, end_time;
	struct hostent *server;
	struct sockaddr_in serversockaddr;
	char msg[buffersize];
	char *serveraddr;
	int msgCounter =0;

	//Create and validate a socket using SOCK_DGRAM
	mySocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(mySocket == -1){
		perror("Error while creating socket");
		return -1;
	}

	//Resolve the server IP and port
	serveraddr = (char *)argv[1];
	port = atoi(argv[2]);
	printf("Input server address is:  %s , and port no. is %d\n", serveraddr,port);
	

	//Get the server object i.e. check if server exists
	server = gethostbyname(serveraddr);
	if(server == NULL){
		fprintf(stderr, " No server found at this address : %s\n", serveraddr);
	}

	//Setting the fields for serversockaddr(The server struct)
	bzero((char *)&serversockaddr, sizeof(serversockaddr));
	serversockaddr.sin_family = AF_INET;
	serversockaddr.sin_port = htons(port);
	bcopy((char *)server -> h_addr, (char *)&serversockaddr.sin_addr.s_addr, server -> h_length);

	int i=0;
	//Populating the server msg with a random characters upto buffersize

	gettimeofday(&start_time, NULL);
	while(msgCounter < 30){
		//Input the message from the user

		//Clearing the input buffer
		bzero(msg, buffersize);

		for(i=0; i < buffersize; i++){
			msg[i] = 'a' + random() % 26;
		}

		printf("Message being sent (%zu): \n",strlen(msg));	

		serverSize = sizeof(serversockaddr);

		//Sending a message to the server
		sendLen = sendto(mySocket, msg, buffersize, 0, (struct sockaddr *)&serversockaddr, serverSize);
		if(sendLen < 0){
			fprintf(stderr, " Error while sending msg : %s\n", msg);
		}

		bzero(msg, buffersize);

		//Getting a response from the server
		sendLen = recvfrom(mySocket, msg, buffersize, 0, (struct sockaddr *)&serversockaddr, &serverSize);
		if(sendLen < 0){
			fprintf(stderr, " Error while receiving msg : %s\n", msg);
		}

		printf("Received echo from server : %s\n", msg);
		msgCounter++;
	}

	gettimeofday(&end_time, NULL);
	time_diff = 1000*(end_time.tv_sec - start_time.tv_sec)+(end_time.tv_usec - start_time.tv_usec)/1000;
	printf("Time difference is : %llu ms\n", time_diff);

	throughput = 30 * buffersize * 1000 / (float)time_diff;
	printf("Throughput time is : %9.6f Bytes/second\n", throughput);

	//Closing the socket
	close(mySocket);
	
	return 0;
}