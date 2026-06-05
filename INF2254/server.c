#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
struct sockaddr_in serv_addr, cli_addr;
int listenfd, connfd, r, w;
socklen_t cli_len;
unsigned short serv_port = 25020;
char serv_ip[] = "127.0.0.1";
char rbuff[128];
char sbuff[256];
int main()
{
    bzero(&serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(serv_port);
    inet_aton(serv_ip, &serv_addr.sin_addr);
    printf("\nTCP MESSAGE LENGTH SERVER\n");
    if((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("SERVER ERROR: Cannot create socket.\n");
        exit(1);
    }
    if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
        printf("SERVER ERROR: Cannot bind.\n");
        close(listenfd);
        exit(1);
    }
    if(listen(listenfd, 5) < 0){
        printf("SERVER ERROR: Cannot listen.\n");
        close(listenfd);
        exit(1);
    }
    while(1){
        printf("\nSERVER: Waiting for client...\n");
        cli_len = sizeof(cli_addr);
        connfd = accept(listenfd,(struct sockaddr*)&cli_addr,&cli_len);
        if(connfd < 0){
            printf("SERVER ERROR: Cannot accept connection.\n");
            continue;
        }
        printf("Client Connected : %s\n",inet_ntoa(cli_addr.sin_addr));
        while(1){
            bzero(rbuff, sizeof(rbuff));
            r = read(connfd, rbuff, sizeof(rbuff));
            if(r <= 0){
                printf("Client Disconnected.\n");
                break;
            }
            rbuff[r] = '\0';
            rbuff[strcspn(rbuff, "\n")] = '\0';
            printf("Received : %s\n", rbuff);
            if(strcmp(rbuff, "exit") == 0){
                printf("Client requested exit.\n");
                close(connfd);
                break;
            }
            sprintf(sbuff,"Message: %s\nLength : %lu",rbuff,strlen(rbuff));
            w = write(connfd, sbuff, strlen(sbuff));
            if(w < 0){
                printf("SERVER ERROR: Cannot send response.\n");
                break;
            }
        }
    }
    close(listenfd);
    return 0;
}
