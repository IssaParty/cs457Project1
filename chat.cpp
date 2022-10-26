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
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <getopt.h>

int serverSide(){

/*
1.  Set up a TCP port and listen for connections (print out IP and PORT is listening on). Waits */

struct addrinfo hints, *res;
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
//currently prints Ip adress that isn't local host. (I'm working on resolving the bug YG)
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
return 0;
}

int clientSide(){

//1.  Set up a TCP connection to the server on the IP and port specified. 
struct addrinfo hints, *res;

int status;
char ipstr[INET6_ADDRSTRLEN];
char port[5];
char message[140];

// arg error Checking

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; //accepts ip4 and ip6
hints.ai_socktype = SOCK_STREAM; //tcp protocol
hints.ai_flags = AF_INET; //auto fills ip with localhost

scanf("%s", port);
scanf("%s", ipstr);

if ((status = getaddrinfo(ipstr, port, &hints, &res)) != 0) {
fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
return 1;
 }
int s;

//set socket setting
s = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

//bind socket

bind (s, res->ai_addr, res->ai_addrlen);

//connect socket
printf("Connecting to server...");
if(connect(s, res->ai_addr, res->ai_addrlen) != -1){
  printf("Connected!");
}

//2.  Prompt the user for a message to send. 
printf("Connected to a friend! You send first.\n");
scanf("%s", message);

//3.  Send the message to the server.
int len, bytes_sent;
len = strlen(message);
bytes_sent = send(s, message, len, 0);

/*
4.  Block to receive a message from the server. 
5.  Receive message and print to screen. 
6.  GOTO step 2. 
*/
return 0;
}
void checkHostName(int hostname){
if(hostname == -1){
  perror("gethostname");
  exit(1);
}
}

void checkHostEntry(struct hostent * hostentry){
  if(hostentry == NULL){
    perror("gethostbyname");
    exit(1);
  }
}

void checkIPbuffer(char *IPbuffer){
  if(NULL == IPbuffer){
    perror("inet_ntoa");
    exit(1);
  }
}

int main(int argc, char* argv[]){

  //set up -p and -s in getopt to save ip and port numbers

  int opt;
  char *port;
  char *ipstr;

  while ((opt =getopt(argc, argv, "p:s:h" )) != -1){
    switch(opt)
    {
      case 'p':
        port = optarg;
        break;
      case 's':
        ipstr = optarg;
        break;
      case 'h':
        printf("Make sure to run the client side this way: \n");
        printf("./chat -p [PORT NUMBER] -s [IP ADDRESS] \n");
        printf("Make sure to run the server side this way: \n ./chat");
        break;
      default:
        printf("Make sure to run the client side this way: \n");
        printf("./chat -p [PORT NUMBER] -s [IP ADDRESS] \n");
        printf("Make sure to run the server side this way: \n ./chat");
        break;
    }
  }
  //serverSide() we need to use this function to connect the host with the ip and port
    char hostbuffer[256];
    char *IPbuffer;
    struct hostent *host_entry;
    int hostname;
  
    // To retrieve hostname
   hostname = gethostname(hostbuffer, sizeof(hostbuffer));
   checkHostName(hostname);
  
    // To retrieve host information
    host_entry = gethostbyname(hostbuffer);
    checkHostEntry(host_entry);
  
    // To convert an Internet network
    // address into ASCII string
    IPbuffer = inet_ntoa(*((struct in_addr*)
                           host_entry->h_addr_list[0]));
    checkIPbuffer(IPbuffer);

    printf("Hostname: %s\n", hostbuffer);
    printf("Host IP: %s", IPbuffer);
    printf("\n");
  return 0;
}
