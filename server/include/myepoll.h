#ifndef _MYEPOLL_H_
#define _MYEPOLL_H_

#define EPOLL_SIZE 64
#define READY_SIZE 64

struct epoll_events tmp,ready[READY_SIZE];

int epoll_init(int sockfd);

int epoll_add(int epfd,int sockfd);

int epoll_delete(int epfd,int sockfd);

#endif
