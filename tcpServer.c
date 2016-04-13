#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

int main(int argc, char *argv[])
{
	
	int mySocket, currClient,addrLen, readLen, bind_val;
	char clientMsg[512];
	struct sockaddr_in server, client;
	//Create the socket
	mySocket = socket(AF_INET,SOCK_STREAM,0);
	if(mySocket == -1){
		puts("Unable to create socket");
		perror("Socket creation failed");
		return 1;
	}

   printf("Port no : %s\n", argv[1]);
   int port = atoi(argv[1]);
   
	puts("Socket created");
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

   /* Bind the socket.*/
   bind_val = bind(mySocket, (struct sockaddr *) &server, sizeof(server));
   if ( bind_val < 0) {
      perror("Error during binding socket");
      return 1;
   }
   
   puts("Waiting for incoming connections");
   addrLen = sizeof(struct sockaddr_in);
   //Listening for incoming connections
   listen(mySocket, 2);

   //Accept the incoming connection
   currClient = accept(mySocket, (struct sockaddr *)&client, (socklen_t *)&addrLen);

   if(currClient < 0){
      perror("Error while accepting the connection.");
   }        

   bzero(clientMsg,512);
   readLen = read(currClient, clientMsg, 512);
   printf(" Message stream received from client(%s : %d) : \n",inet_ntoa(client.sin_addr), ntohs(client.sin_port));
   fprintf(stderr," Message is from client(%s : %d) :\n ", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

   while(readLen!= 0){

      if(readLen < 0){
         perror("Error reading from socket");
         return 1;
      }
      //Appending the message stream to the file output
      printf(" %s ", clientMsg);
               
      bzero(clientMsg,512);   
      readLen = read(currClient, clientMsg, 512);
      
   }

   //Read until the end of file
   puts("\n Client has disconnected.");
   fflush(stdout);

   puts("Exiting here");
	return 0;
}