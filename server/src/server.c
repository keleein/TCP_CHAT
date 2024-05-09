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

void server_accept(int sockfd,int epfd)
{
	//添加客户端到红黑树以监听发送
	int connfd = accept(sockfd,NULL,NULL);
	if(connfd < 0)
	{
		perror("server_accept: accept");
		exit(-1);
	}
	//添加客户端到epoll树进行监听
	int ret = epoll_add(epfd,connfd);
	if(ret < 0)
	{
		printf("client miss...\n");
	}
}

void server_recv_data(int sockfd,int epfd,char **buf)
{
	//接收客户端信息
	char tmp[BUF_SIZE] = {0};
	int ret = recv(sockfd,tmp,sizeof(tmp),0);
	if(ret < 0)
	{
		perror("server_recv_data");
		exit(-1);
	}else if(ret == 0)
	{
		//客户端失去连接删除红黑树节点和链表节点
		if(epoll_delete(epfd,sockfd) == 0)
		{
			printf("client %d has disconnected!\n",fd);
			return;
		}else{
			//delete failed -> server stop
			printf("server_recv_data: epoll_delete error!\n");
			exit(-1);
		}
	}else{
		//recv success!
		*buf = (char*)malloc(BUF_SIZE*sizeof(char));
		strcpy(*buf,tmp);
		return;
	}
}

void data_case(char *buf,)
{

}

