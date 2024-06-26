#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

int server_init()
{
	//create server socket
	int server = socket(AF_INET,SOCK_STREAM,0);
	if(server < 0)
	{
		perror("socket");
		exit(-1);
	}

	//set socket property reuseaddr
	int on = 1;
	int ret = setsockopt(server,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
	if(ret < 0)
	{
		perror("setsockopt");
		exit(-1);
	}

	//bind net addr
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	ret = bind(server,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		perror("bind");
		exit(-1);
	}

	//listen queue
	ret = listen(server,5);
	if(ret < 0)
	{
		perror("listen");
		exit(-1);
	}

	return server;
}

int client_disconnect(int epfd,client_info *head,int connfd)
{
	//客户端断开连接删除红黑树节点和链表信息
	struct epoll_events tmp;
	tmp.data.fd = connfd;
	tmp.events = EPOLLIN;
	int ret = epoll_ctl(epfd,EPOLL_CTL_DEL,connfd,&tmp);
	if(ret < 0)
		return -1;
	delete(head,connfd);
	return 0;
}
