#include <sys/epoll.h>
#include <stdlib.h>
#include <unistd.h>
#include "myepoll.h"

int epoll_init(int sockfd)
{
	 //创建一个epoll红黑树
        int epfd = epoll_create(EPOLL_SIZE);

        //添加服务器到红黑树
        tmp.data.fd = sockfd;
        tmp.events = EPOLLIN;
        int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&tmp);
        if(ret != 0)
        {
                perror("epoll_ctl_init");
                exit(-1);
        }
	
	return epfd;
}

int epoll_add(int epfd,int sockfd)
{
	tmp.data.fd = sockfd;
        tmp.events = EPOLLIN;
        int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&tmp);
	if(ret != 0)
	{
		perror("epoll_add: epoll_ctl_add");
		return -1;
	}
	return 0;
}

int epoll_delete(int epfd,int sockfd)
{
	tmp.data.fd = sockfd;
	tmp.events = EPOLLIN;
	int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,sockfd,&tmp);
	if(ret != 0)
	{
		perror("epoll_delete: epoll_ctl_del");
		return -1;
	}
	return 0;
}
