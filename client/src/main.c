#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"
#include "thread.h"

#define WRITEBUF 64

int main()
{
	//初始化客户端
	int client = client_init();
	if(client < 0)
	{
		perror("client_init");
		exit(-1);
	}

	//创建单一线程接收信息并显示
	pthread_t thread_read;
	pthread_create(&thread_read,NULL,read_info,(void*)&client);
	pthread_detach(&thread_read);

	//主线程发送客户端消息
	char buf[WRITEBUF] = {0};
	while(1)
	{
		fgets(buf,sizeof(buf),stdin);
		buf[strlen(buf)-1] = '\0';
		int ret = send(client,buf,strlen(buf),0);
		if(ret < 0)
		{
			perror("send");
			exit(-1);
		}
		memset(buf,0,sizeof(buf));
	}

	return 0;
}
