
1) Relevant files included : 

a) Makefile -
 Used to compile and create executables for the programs. We can compile all the programs for the assignment by running the make command. The directions to run the makefile are as follows : 

- Copy all the files in Source_code folder to the directory of Makefile
- Open a terminal in Linux.
- Navigate to the folder in which the makefile and the .c program files are located.
- Type in 'make -f Makefile.hw1'
- All the executables for the .c programs will be created in the folder.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

b) tcpServer.c :
 This file acts as the TCP Server. It takes 1 input parameter from the command line. This is the port no. at which the server is supposed to run. Any valid IP port can serve as the input port no. Makefile is used to create an executable from the .c file. The tcpServer.o file is created after running the makefile. We need to store the server's output in the serverOutput.txt file.  We can then start the server by running the running the following command in a Linux terminal: 

./tcpServer 8207 > serverOutput.txt

(8207 is the port no. that we provide for the server.)

The server creates a TCP socket at localhost from the input port no.  If the socket is successfully created, the server prints the port no. and a success message. The server then listens for incoming messages. It has an input buffer of length 512 bytes, which is repeatedly filled and written to the output buffer until there are no more messages from the client. When the server receives a message from a client, it prints the client's IP address and port number to its stderr output stream. It then reads the client message into its input buffer and prints it(this print is written to the serverOutput.txt file). The server keeps on reading messages and printing them to serverOutput.txt until it has read the last message, i.e. the message length is zero. After it has printed the client message content, the server exits.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

c) tcpClient.c -  This file acts as the client. It takes 2 input parameters from the command line - the server IP address and server port no. respectively. Additionally, the client needs to send the clientInput.txt file which is the input stream that the client sends to the server. The tcpClient.o file is created after running the makefile. We can then start the server by running the running the following command in a Linux terminal: 

cat clientInput.txt | ./tcpClient 127.0.0.1 8207

This command takes the content of clientInput.txt as the input for the client program. 127.0.0.1 is the server's IP address. 8207 is the server port no. The client first attempts to create a TCP  socket for the server address specified in the command line arguments. It has a message buffer of size 512 which it uses to send as a message to the server. If the socket is created successfully, a success message is printed otherwise an error message is printed. The client then repeatedly sends messages of size 512 bytes from the clientInput.txt file to the server until it has reached the end of the file. After it has reached the EOF, the client exits. After this, we find that the content of the clientInput.txt file has been copied to the serverOutput.txt file. 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

d) serverOutput.txt - An empty .txt file that contains the content of the server's stdout output stream the clientInput.txt file once the server has written all the client's messages to this file. 

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

e) clientInput.txt - A .txt file that contains some text. It is used as input for the client program. The client considers each individual word as a separate message.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

f) udpServer.c -  This file acts as the UDP Server. It takes 3 input parameters from the command line - the server port no., the client message size in bytes and the sleep time in milliseconds respectively. Makefile is used to create an executable from the .c file. The udpServer.o file is created after running the makefile. We can then start the server by running the running the following command in a Linux terminal: 

./udpServer 9207 1024 10

9207 is the port no. the server starts on, 1024 is the client message size in bytes and 10 is the no. of milliseconds the server sleeps for(to simulate latency). The server attempts to create a UDP socket at the port provided. It initialises a buffer with the message size provided. It also has a message counter(msgCounter) which starts at 0 and increments each time a message is sent to the client. If the socket is created successfully , a success message is shown otherwise an error message is displayed and the server exits. The server then listens for messages from a client. Once it receives a message it prints the client's IP address and port and the size of the message in bytes. It creates a response message in the format "ACK <msgCounter>" where msgCounter is a no. that is incremented for each time the server receives a message. Server then simulates network latency by sleeping for the specified milliseconds( by using the usleep() function). It then sends the created response message back to the client. It keeps repeating this process until the msgCounter has reached 30 i.e. 30 messages have been received. After this, the server exits.
------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

g) udpClient.c - This file acts as the UDP Client. It takes 3 input parameters from the command line - the server IP address, its port no. and the client message size in bytes. Makefile is used to create an executable from the .c file. The udpServer.o file is created after running the makefile. We can then start the server by running the running the following command in a Linux terminal: 

./udpClient 127.0.0.1 9207 1024

127.0.0.1 is the server IP address, 9207 is the port no. the server starts on, 1024 is the client message size in bytes. The client first attempts to create a UDP socket for the server address specified in the command line arguments. If there is no server found at this address, an error message is printed and the client exits. Otherwise, the client records the start time at which it is going to send the message. It generates a random text string consisting of lowercase alphabets, of the length specified in the arguments. It sends this generated message to the server, and waits for an acknowledgment. Once it receives this acknowledgment, it prints it to the console. It repeats this for 30 messages. After this it records the end time for this process. The client then calculates the throughput achieved by the program using the formula

Throughput = 30 * (buffer size)/(end time - start time) bytes/second.

It prints the throughput achieved to the console. Client then closes the socket and exits.

2) References -

a) http://www.binarytides.com/programming-udp-sockets-c-linux/
b) https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/udpclient.c
c) https://www.cs.cmu.edu/afs/cs/academic/class/15213-f99/www/class26/udpserver.c






