#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#define BUFF_SIZE 200
#define IP_ADDRESS "127.0.0.1"
#define PORT 1234

using namespace std;

int main() {
    struct sockaddr_in server_addr;
	int sockfd, status;

	//setup the server address
	server_addr.sin_family = PF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = inet_addr(IP_ADDRESS);

	//connect to the server	
	sockfd = socket (PF_INET, SOCK_STREAM, 0);
	connect (sockfd, (struct sockaddr *) &server_addr, sizeof(struct sockaddr_in));


	// Server_Request_Procedure(sockfd); //Call procedure you wish to perform
    

    char msg_recv[BUFF_SIZE], msg_send[BUFF_SIZE];   // message declaration
    while (1) {
        memset(msg_recv, '\0', sizeof(msg_recv));   // reset the buffer
        // puts(msg_recv);
        // bzero(msg_recv, strlen(msg_recv));
        // printf("original len = %ld\n", strlen(msg_recv));
        read(sockfd, msg_recv, BUFF_SIZE);
        // printf("after rec len = %ld\n", strlen(msg_recv));
        // printf("msg_recv = %s, len = %ld\n", msg_recv, strlen(msg_recv));
        printf("%s", msg_recv);
        memset(msg_send, '\0', sizeof(msg_send));
        scanf("%s", msg_send);
        // gets(msg_send);
        write(sockfd, msg_send, BUFF_SIZE);

        if (!strcmp(msg_send, "3")) {
            break;
        }

        // memset(msg_recv, '\0', sizeof(msg_recv));   // reset the buffer
        // // puts(msg_recv);
        // // bzero(msg_recv, strlen(msg_recv));
        // read(sockfd, msg_recv, BUFF_SIZE);
        // // printf("msg_recv = %s, len = %ld\n", msg_recv, strlen(msg_recv));
        // printf("%s", msg_recv);
        // memset(msg_send, '\0', sizeof(msg_send));
        // scanf("%s", msg_send);
        // // gets(msg_send);
        // write(sockfd, msg_send, BUFF_SIZE);
    }
    
	close(sockfd);	
	return 0;

}