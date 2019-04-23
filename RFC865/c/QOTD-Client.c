/***********************************************************************************
* Date: November 6, 2016
* Purpose: TCP Client to pull a quote from QOTD website.
***********************************************************************************/ 

#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SIZE sizeof(struct sockaddr_in)
// #define IPADDR   "84.95.139.148"  // alpha.mike-r.com QOTD
#define IPADDR   "98.184.69.54" //djxmmx.net QOTD

int main()
{
  int sockfd;
  int bytesReceived = 0;
  //allows for fluid message (no breaks)
  char recvBuff[256]; //buffer of allowed received bytes
  //memset fills memory with a constant byte of 0
  memset(recvBuff, '0', sizeof(recvBuff));
  struct sockaddr_in server;

  server.sin_family = AF_INET;
  //sets the port number to 17, matching the QOTD server
  server.sin_port = htons(17); //port 17 is the specified port for QOTD cli/serv
  // convert and store the server's IP address
  server.sin_addr.s_addr = inet_addr(IPADDR);
  
  // set up the transport end point
  //SOCK_STREAM provides reliable connection-based byte streams
  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
    perror("socket call failed");
    exit(-1);
    }

  // connect the socket to the server's address
  if (connect(sockfd, (struct sockaddr *)&server, SIZE) == -1)
    {
    perror("connect call failed");
    exit(-1);
    }
	
  while((bytesReceived = read(sockfd, recvBuff, sizeof(recvBuff)-1)) > 0)
  {
	printf("Bytes received: %d\n\n", bytesReceived);
	printf(recvBuff, 1, bytesReceived); //prints quote from www.djxmmx.net
  }
  
  //error checking to let user know when bytes not read
  if(bytesReceived < 0)
	printf("Data not read completely\n");
}  // end main