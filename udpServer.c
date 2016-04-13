#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

   int main(int argc, char *argv[])
   {
      
      int mySocket, currClient,addrLen, readLen, bind_val;
      int msgCounter =0;
      int bufferSize= atoi(argv[2]);
      int sleepTime = atoi(argv[3]);
      char clientMsg[bufferSize];
      char clientResponseMsg[bufferSize];
      struct sockaddr_in server, client;
      struct hostent *hostp;
      //Create the socket
      mySocket = socket(AF_INET,SOCK_DGRAM,0);
      char *hostaddrp;
      if(mySocket == -1){
         puts("Unable to create socket");
         perror("Socket creation failed");
         return 1;
      }

      int port = atoi(argv[1]);
      printf("Socket created at Port no : %d\n", port);

      bzero((char *)&server, sizeof(server));
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
      addrLen = sizeof(client);


      while(1){        

         bzero(clientMsg,bufferSize);
         readLen = recvfrom(mySocket, clientMsg, bufferSize, 0, (struct sockaddr *)&client, &addrLen);

         if(readLen < 0){
            perror("Error reading from socket");
            return -1;
         }            

         hostp = gethostbyaddr((const char *)&client.sin_addr.s_addr, sizeof(client.sin_addr.s_addr), AF_INET);
         if(hostp == NULL){
            puts("ERROR ON gethostbyaddr");
            return -1;
         }

         hostaddrp = inet_ntoa(client.sin_addr);
         if (hostaddrp == NULL)
            error("ERROR on inet_ntoa\n");

         bzero(clientResponseMsg,bufferSize);
         sprintf(clientResponseMsg, "ACK %d", ++msgCounter);
         printf("Server received datagram NO :%d of length %zu from : %s (%s : %d) \n",msgCounter, strlen(clientMsg), hostp->h_name, hostaddrp, ntohs(client.sin_port));

         //Simulate server latency

         printf("Sleeping for %d milliseconds..\n", sleepTime );
         usleep(sleepTime*1000);

         //Send a response back to client
         readLen = sendto(mySocket, clientResponseMsg, strlen(clientResponseMsg), 0, (struct sockaddr *)&client, addrLen);

         if(readLen < 0){
            puts("Error in sending response to client");
         }
         
         if(msgCounter ==30 ){
            break;
         }

      }
      close(mySocket);

      puts("Exiting here");
      return 0;
   }