#include <stdio.h>
#include "server_init.h"

#define BUF_SIZE 64
#define EPOLL_SIZE 64
#define READY_SIZE 64

int main()
{
	//初始化TCP服务器
	int server = server_init();
	
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
			int fd = ready[i].data.fd;
			if(fd == server)
			{
				//添加客户端到红黑树以监听发送
				int connfd = accept(server,NULL,NULL);
				if(connfd < 0)
				{
					perror("accept");
					exit(-1);
				}
				tmp.data.fd = connfd;
				tmp.events = EPOLLIN;
				ret = epoll_ctl(epfd,EPOLL_CTL_ADD,connfd,&tmp);

				//使用链表存储客户端信息以便广播和组播

			}else{
				//广播消息

			}
		}
	}
	return 0;
}

