#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "myepoll.h"

#define PORT 5555	//server port
#define BUF_SIZE 64

int server_init();

void server_accept(int sockfd,int epfd);

void server_recv_data(int sockfd,int epfd,char **buf);

#endif
