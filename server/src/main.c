#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "server.h"
#include "linklist.h"

#define BUF_SIZE 64
#define EPOLL_SIZE 64
#define READY_SIZE 64

int main()
{
	//初始化TCP服务器
	int server = server_init();

	//初始化一个信息链表
	client_info *head = list_init();
	struct sockaddr_in client_addr;
	int client_len = 0;

	//创建一个epoll红黑树
	int epfd = epoll_create(EPOLL_SIZE);

	//添加服务器到红黑树
	struct epoll_events tmp,ready[READY_SIZE];
	tmp.data.fd = server;
	tmp.events = EPOLLIN;
	int ret = epoll_ctl(epfd,EPOLL_CTL_ADD,server,&tmp);
	if(ret != 0)
	{
		perror("epoll_ctl_init");
		exit(-1);
	}

	//epoll监听客户端连接和发送
	char buf[BUF_SIZE] = {0};
	while(1)
	{
		int max = epoll_wait(epfd,&ready,-1);
		if(max < 0)
		{
			perror("epoll_wait");
			exit(-1);
		}
		for(int i = 0; i < max; i++)
		{
			//服务器只接受EPOLLIN信息
			if(ready[i].revents & EPOLLIN)
			{
				int fd = ready[i].data.fd;
				if(fd == server)
				{
					//添加客户端到红黑树以监听发送
					int connfd = accept(server,&client_addr,&client_len);
					if(connfd < 0)
					{
						perror("accept");
						exit(-1);
					}
					tmp.data.fd = connfd;
					tmp.events = EPOLLIN;
					ret = epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&tmp);

					//使用链表存储客户端信息以便广播和组播
					insert(head,connfd,inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));		
				}else{
					//接收客户端信息
					ret = recv(fd,buf,sizeof(buf),0);
					if(ret < 0)
					{
						perror("recv");
						exit(-1);
					}else if(ret == 0)
					{
						if(client_disonnect(epfd,head,connfd) < 0)
						{
							perror("client_disconnect");
							exit(-1);
						}
					}else{
						//默认buf信息为广播信息，@开头
					}
				}
			}
		}
	}
	return 0;
}

