#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <stdlib.h>
#include <stdio.h>

const int BUF_SIZE = 10000000;

typedef struct client {
    int id;
    char msg[BUF_SIZE];
} t_client;

t_client clients[1000];

fd_set readReady, writeReady, active;

int servFd, connFd, max, nextId;
struct sockaddr_in servaddr, cli; 
char readBuf[BUF_SIZE], writeBuf[BUF_SIZE];

void ft_exit(char* msg) {
    write(2, msg, strlen(msg));
    write(2, "\n", 1);
    exit(1);
}

void ft_broadcast(int myFd) {
    for (int curFd = 0; curFd <= max; curFd++) {
        if (!FD_ISSET(curFd, &writeReady) || curFd == myFd)
            continue;
        send(curFd, writeBuf, strlen(writeBuf), 0);
    }
}

int main(int argc, char** argv) {
	if (argc != 2)
        ft_exit("Wrong number of arguments");
    socklen_t len;

	// socket create and verification 
	servFd = socket(AF_INET, SOCK_STREAM, 0); 
	if (servFd == -1) { 
		ft_exit("Fatal error");
	}

	// assign IP, PORT 
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(atoi(argv[1]));
  
	// Binding newly created socket to given IP and verification 
	if ((bind(servFd, (const struct sockaddr *)&servaddr, sizeof(servaddr))) != 0) { 
		ft_exit("Fatal error");
	} 
	if (listen(servFd, 10) != 0) {
		ft_exit("Fatal error"); 
	}

    FD_SET(servFd, &active);
    max = servFd;
    while (1) {
        readReady = writeReady = active;
        if (select(max + 1, &readReady, &writeReady, 0, 0) < 0) {
            continue;
        }
        for (int curFd = 0; curFd <= max; curFd++) {
            if (!FD_ISSET(curFd, &readReady))
                continue;
            
            if (curFd == servFd) {
                len = sizeof(cli);
                connFd = accept(servFd, (struct sockaddr *)&cli, &len);
                if (connFd < 0) continue;
                max = (max < connFd) ? connFd : max;
                FD_SET(connFd, &active);
                clients[connFd].id = nextId++;
                sprintf(writeBuf, "server: client %d just arrived\n", clients[connFd].id);
                ft_broadcast(curFd);
                continue;
            }

            int res = recv(curFd, readBuf, BUF_SIZE, 0);
            if (res <= 0) {
                sprintf(writeBuf, "server: client %d just left\n", clients[curFd].id);
                ft_broadcast(curFd);
                close(curFd);
                FD_CLR(curFd, &active);
                continue;
            }
            int msg_idx = strlen(clients[curFd].msg);
            for (int idx = 0; idx < res; idx++, msg_idx++) {
                clients[curFd].msg[msg_idx] = readBuf[idx];
                if (readBuf[idx] == '\n') {
                    clients[curFd].msg[msg_idx] = 0;
                    sprintf(writeBuf, "client %d: %s\n", clients[curFd].id, clients[curFd].msg);
                    ft_broadcast(curFd);
                    msg_idx = -1;
                }
            }
                break;
        }
    }
    	

}