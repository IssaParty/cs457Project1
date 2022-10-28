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
#include <string>
#define BACKLOG 10
#define PORT 3490
#define MAX_BUFF 140

void checkIPbuffer(char *IPbuffer){
  if(NULL == IPbuffer){
    perror("inet_ntoa");
    exit(1);
  }
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

char* getIP(){
    
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
    return IPbuffer;
}


int serverSide(){
/*
1.  Set up a TCP port and listen for connections (print out IP and PORT is listening on). Waits */
bool running = true ; 
struct addrinfo hints, *res, *p;
struct sockaddr_storage their_addr;
int status;
int i;
char ipstr[INET6_ADDRSTRLEN];

// arg error Checking

memset(&hints, 0, sizeof hints);
hints.ai_family = AF_UNSPEC; //accepts ip4 and ip6
hints.ai_socktype = SOCK_STREAM; //tcp protocol
hints.ai_flags = AI_PASSIVE; //auto fills ip with localhost

//
if ((status = getaddrinfo(NULL, "3490", &hints, &res)) != 0) {
fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
return 1;
 }
int sock_fd;

//set socket setting
sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
if((i = bind (sock_fd, res->ai_addr, res->ai_addrlen)) != 0){
  fprintf(stderr, "bind error: %s\n", gai_strerror(i));
}

if((status = listen(sock_fd, BACKLOG)) != 0){
  printf("",status);
  fprintf(stderr, "listen error: %s\n", gai_strerror(status) );
} 
else{
  printf("Welcome to Chat!\nWaitingfor a connection \n%s port %i\n", getIP(), PORT);
  
}
socklen_t addr_size = sizeof their_addr;
int server_sock;
if(server_sock = accept(sock_fd, (struct sockaddr *)&their_addr, &addr_size)==-1){
 fprintf(stderr, "accept error: %s\n", gai_strerror(server_sock) );
 return 0;
}
else {
    printf("Found a friend! You receive first.\n");
}


//infinitely prompts server for input and restarts loop of input is too long.
while(true){
  char client_message[MAX_BUFF];
  char server_message[MAX_BUFF];
  char buffer[1024] = {0};
  printf("%ld\n",read(server_sock, buffer , 1024));
  
  printf("Friend: %s\n", buffer);

  while(true){
    printf("You: ");
    scanf("%s", server_message);
    if( strlen(server_message) > MAX_BUFF){
        printf("Input too long.\n");
        continue;
    }
    break;
  }
  send(server_sock, server_message, strlen(server_message), 0);
}
return 0;
}

int clientSide(char *portNo, char *ip){
//1.  Set up a TCP connection to the server on the IP and port specified. 
struct addrinfo hints, *res;

int status;
char *ipstr = ip;
char *port = portNo;

 //int port = atoi(portNo);

memset(&hints, 0, sizeof hints); 
hints.ai_family = AF_UNSPEC; //accepts ip4 and ip6
hints.ai_socktype = SOCK_STREAM; //tcp protocol

if ((status = getaddrinfo(ipstr, port, &hints, &res)) != 0) {
fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
return 1;
 }
int sock_fd;

sock_fd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

printf("Connecting to server...\n");
if(connect(sock_fd, res->ai_addr, res->ai_addrlen) != -1){
  printf("Connected!\n");
}
else{
    printf("Could not connect to server with ip: %s and port:%s \n", ipstr, port);
    return 0;
}

//2.  Prompt the user for a message to send. 
printf("Connected to a friend! You send first.\n");

//Infinitely prompts user for input and restarts if input is too long
while(true){
    char client_message[MAX_BUFF];
    char server_message[MAX_BUFF];
    char buffer [1024] = {0};
    printf("YOU: ");
    scanf("%s", client_message);

    if(strlen(client_message) > MAX_BUFF){
        printf("Input too long.\n");
        continue;
    }
    printf("made\n");
    send(sock_fd, client_message, strlen(client_message), 0);
    
    //block for server response
    
    printf("%ld\n",read(sock_fd, buffer ,1024));

    printf("Friend: %s\n", server_message);
  }
}

int main(int argc, char* argv[]){
  //serverSide() we need to use this function to connect the host with the ip and port
   //set up -p and -s in getopt to save ip and port numbers
  
  int opt;
  char *port;
  char *ipstr;
  if(argc <=1){
  serverSide();
  return 0;
  }
  
  // else{
  
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
        printf("Make sure to run the server side this way: \n ./chat \n");
        break;
      default:
        printf("Make sure to run the client side this way: \n");
        printf("./chat -p [PORT NUMBER] -s [IP ADDRESS] \n");
        printf("Make sure to run the server side this way: \n ./chat \n");
        break;
    }
  }
  clientSide(port, ipstr);//}
  return 0;
}
