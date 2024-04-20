#include <stdio.h>
#include "client.h"

//初始化客户端连接
int client_init()
{
	//初始化client
	int client = socket(AF_INET,SOCK_STREAM,0);
	if(client < 0)
	{
		return -1;
	}

	//连接服务器
	struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = inet_addr(SERVER_ADDR);
	int ret = connect(client,(struct sockaddr*)&server_addr,sizeof(server_addr));
	if(ret < 0)
	{
		return -1;	
	}

	return client;
}
