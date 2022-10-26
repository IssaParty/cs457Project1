/*******************************************
* Group Name  : FLCL

* Member1 Name: Issa Ahmed
* Member1 SIS ID: 832161534
* Member1 Login ID: aissaam

* Member2 Name: Carlos Flores
* Member2 SIS ID: 832394284
* Member2 Login ID: carlosf

* Member3 Name: Yosief Gebremedhin
* Member3 SIS ID: 830031364
* Member3 Login ID: ygebreme
********************************************/

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int serverSide(){

/*
1.  Set up a TCP port and listen for connections (print out IP and PORT is listening on). Waits */

struct addrinfo hints, *res, *p;
int status;
char ipstr[INET6_ADDRSTRLEN];

// arg error Checking

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; //accepts ip4 and ip6
hints.ai_socktype = SOCK_STREAM; //tcp protocol
hints.ai_flags = AF_INET; //auto fills ip with localhost

//
if ((status = getaddrinfo("192.168.122.1", "3490", &hints, &res)) != 0) {
fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
return 1;
 }
int s;

//set socket setting
s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
//bind socket
bind (s, res->ai_addr, res->ai_addrlen);

//extracting ip address the socket is binded to
inet_ntop(res->ai_family, res->ai_addr, ipstr, sizeof ipstr);
printf(ipstr);
printf("\n");


/*
2.  Accept connection from client 
3.  Block to receive a message from the client. 
4.  Receive message and print to screen. 
5.  Prompt the user for a message to send. 
6.  Send the message to the client. 
7.  GOTO step 3. 
*/

}

int clientSide(){

/*
1.  Set up a TCP connection to the server on the IP and port specified. 
2.  Prompt the user for a message to send. 
3.  Send the message to the server. 
4.  Block to receive a message from the server. 
5.  Receive message and print to screen. 
6.  GOTO step 2. 
*/

}

int main(int argc, char* argv[]){
  return 0;
}
