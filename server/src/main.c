#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "server.h"
#include "linklist.h"
#include "myepoll.h"

#define BUF_SIZE 64

int main()
{
	//初始化TCP服务器
	int server = server_init();

	//创建一个epoll红黑树
	int epfd = epoll_init(server);

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

					//添加客户端到epoll树进行监听
					epoll_add(epfd,connfd);

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
						//客户端失去连接删除红黑树节点和链表节点
						if(epoll_delete(epfd,fd) == 0)
						{
							printf("client %d has disconnected!\n",fd);
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

