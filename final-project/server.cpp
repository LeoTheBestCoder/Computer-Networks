#include <cstdio>
#include <cstdlib>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <vector>

#define BUFF_SIZE 200
#define PORT 1234
using namespace std;
    
char msg_recv[BUFF_SIZE], msg_send[BUFF_SIZE];

class Student {

public:
    char id[100], email[100];
    Student() {}
};

int main () {
	struct sockaddr_in myaddr;
    struct sockaddr_in client_addr;
    struct hostent *hent;

	int sockfd, streamfd, port, status, addr_size;

	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(PORT);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	sockfd = socket(PF_INET, SOCK_STREAM, 0);
    
    // check if TCP connection is setup successfully
    if(sockfd < 0){
        printf("The socket is not opened\n");
        exit(1);
    } else
        printf("The socket opened successfully\n");
    
    if(bind(sockfd, (struct sockaddr *) &myaddr, sizeof(struct sockaddr_in)) < 0){
        printf("ERROR on binding\n");
        exit(-1);
    }

	listen(sockfd, 10);
	addr_size = sizeof(client_addr);	

    // read file and store the data into st_list
    vector<Student> st_list;
    FILE *fp;
    if ((fp = fopen("query.txt", "r")) == NULL) {
        printf("File 'query.txt' doesn't exist\n");
        exit(-1);
    }
    else {
        Student st;
        while (fscanf(fp, "%s %s", st.id, st.email) != EOF) {
            st_list.push_back(st);
        }
    }
    // for (const Student s: st_list) {
    //     printf("%s %s\n", s.id, s.email);
    // }

	while(1) {
        printf("Waiting for connection...\n");
	    streamfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &addr_size);	
	    // handle_client(connfd);     //Call the procedure you wish to perform
        memset(msg_send, '\0', sizeof(msg_send));   // clear the buffer
        while (1) {
            memset(msg_send, '\0', sizeof(msg_send));   // clear the buffer
            strcpy(msg_send, "What's your requirement? 1.DNS 2.QUERY 3.QUIT : ");
            write(streamfd, msg_send, strlen(msg_send));
            
            memset(msg_recv, '\0', sizeof(msg_recv));   // clear the buffer
            read(streamfd, msg_recv, BUFF_SIZE);

            if (!strcmp(msg_recv, "1")) {
                memset(msg_send, '\0', sizeof(msg_send));
                strcpy(msg_send, "Input URL address : ");

                write(streamfd, msg_send, strlen(msg_send));
                memset(msg_recv, '\0', sizeof(msg_recv));   // clear the buffer
                read(streamfd, msg_recv, BUFF_SIZE);

                hent = gethostbyname(msg_recv);
                if (hent == NULL) {
                    printf("No such DNS\n");
                    memset(msg_send, '\0', sizeof(msg_send));
                    strcpy(msg_send, "ERROR: No such DNS\n\n");
                    write(streamfd, msg_send, strlen(msg_send));
                }
                else {
                    printf("IP Address: %s\n", inet_ntoa(*(struct in_addr*) hent->h_addr));
                    memset(msg_send, '\0', sizeof(msg_send));
                    strcpy(msg_send, "address get from the domain name : ");
                    strcat(msg_send, inet_ntoa(*(struct in_addr*) hent->h_addr));
                    strcat(msg_send, "\n\n");
                    write(streamfd, msg_send, strlen(msg_send));
                }

            }
            else if (!strcmp(msg_recv, "2")) {
                memset(msg_send, '\0', sizeof(msg_send));
                strcpy(msg_send, "Input student ID : ");
                write(streamfd, msg_send, strlen(msg_send));
                memset(msg_recv, '\0', sizeof(msg_recv));
                read(streamfd, msg_recv, BUFF_SIZE);
                bool find = false;
                for (int i = 0; i < st_list.size(); i++) {
                    if (!strcmp(st_list[i].id, msg_recv)) {
                        memset(msg_send, '\0', sizeof(msg_send));
                        strcpy(msg_send, "Email get from the server : ");
                        strcat(msg_send, st_list[i].email);
                        strcat(msg_send, "\n\n");
                        write(streamfd, msg_send, strlen(msg_send));
                        printf("%s\n", st_list[i].email);
                        find = true;
                        break;
                    }
                }
                if (!find) {
                    printf("No such student ID\n");
                    memset(msg_send, '\0', sizeof(msg_send));
                    strcpy(msg_send, "Email get from the server : No such student ID\n\n");
                    write(streamfd, msg_send, strlen(msg_send));
                }
            }
            else if (!strcmp(msg_recv, "3")) {
                break;
            }
            else {
                memset(msg_send, '\0', sizeof(msg_send));
                strcpy(msg_send, "Invalid requirement! (should between 0~3)\n\n");
                write(streamfd, msg_send, strlen(msg_send));
            }
        }        
	}
    close(streamfd);
    return 0;
}
