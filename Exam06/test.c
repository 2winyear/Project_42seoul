#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

int max, curFd, id;
int sockfd, connfd;
struct sockaddr_in servaddr, cli; 

const int BUFFER_SIZE = 1000000;

socklen_t len;

char writeBuf[BUFFER_SIZE];
char readBuf[BUFFER_SIZE];


fd_set active, readReady, writeReady;

typedef struct {
    int id;
    char msg[BUFFER_SIZE];
} t_socket;

t_socket sock[1000];

void ft_exit(char* msg)
{
    write(2, msg, strlen(msg));
    exit(1);
}

void ft_broadcast(int curFd)
{
    for (int fd = 0; fd <= max; fd++) {
        if (!FD_ISSET(fd, &writeReady) || fd == curFd)
            continue ;
        send(fd, writeBuf, strlen(writeBuf), 0);
    }
}


int main(int argc, char **argv) {
    if (argc != 2)
        ft_exit("Wrong number of arguments\n");

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); //serverSock
	if (sockfd == -1)
		ft_exit("Fatal error\n");
	bzero(&servaddr, sizeof(servaddr)); //clients

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1])); 
  
	// Binding newly created socket to given IP and verification 
	
    if ((bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
        ft_exit("Fatal error\n");

    if (listen(sockfd, 10) != 0)
        ft_exit("Fatal error\n");

    max = sockfd;
    FD_SET(sockfd, &active);
    while (1) {
        readReady = writeReady = active;
        if (select(max + 1, &readReady, &writeReady, 0, 0) <= 0)
            continue;
        
        for (int curFd = 0; curFd <= max; curFd++) {
            if (!FD_ISSET(curFd, &readReady))
                continue;
            if (curFd == sockfd) {
                len = sizeof(cli);
                connfd = accept(sockfd, (struct sockaddr *)&cli, &len);
                if (connfd < 0) continue;
                sprintf(writeBuf, "server: client %d just arrived\n", id);
                sock[connfd].id = id++;
                ft_broadcast(connfd);
                FD_SET(connfd, &active);
                max = max > connfd ? max : connfd;
                continue;
            }

            int res = recv(curFd, readBuf, BUFFER_SIZE, 0);
            
            if (res <= 0)
            {
                sprintf(writeBuf, "server: client %d just left\n", sock[curFd].id);
                ft_broadcast(curFd);
                close(curFd);
                FD_CLR(curFd, &active);
                continue;
            }
            for (int idx = 0, msg_idx = strlen(sock[curFd].msg); idx < res; idx++, msg_idx++)
            {
                sock[curFd].msg[msg_idx] = readBuf[idx];
                if (readBuf[idx] == '\n')
                {
                    sock[curFd].msg[idx]=0;
                    sprintf(writeBuf, "client %d: %s\n", sock[curFd].id, sock[curFd].msg);
                    ft_broadcast(curFd);
                    sock[curFd].msg[0] = 0;
                    msg_idx=-1;
                }
            }
            break;
        }

    }



}