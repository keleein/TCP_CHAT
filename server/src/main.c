#include <stdio.h>
#include "server.h"
#include "linklist.h"
#include "myepoll.h"

int main()
{
	//初始化TCP服务器
	int server = server_init();

	//创建一个epoll红黑树
	int epfd = epoll_init(server);

	//epoll监听客户端连接和发送
	char *buf = NULL;
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
					server_accept(fd,epfd);
				}else{
					server_recv_data(fd,epfd,&buf);
				}
			}
		}
	}
	return 0;
}

