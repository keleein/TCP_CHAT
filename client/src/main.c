#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "client.h"

#define WRITEBUF 64

int main()
{
	//欢迎界面
	int ret = 0;
	while(1)
	{
		printf("---------welcome----------");
		printf("---------1.login----------");
		printf("--------2.sign up--------");
		printf("---------3.exit-----------");
		int jud = 0;
		scanf("%d",&jud);
		switch(jud){
			case 1:
				//登录
				int client = login();
				if(client < 0)
				{
					printf("login failed! please try again!\n");
					continue;
				}
				homepage();
				break;
			case 2:
				//注册
				ret = signup();
				if(ret < 0)
				{
					printf("sign up failed! please try again!\n");
					continue;
				}
				printf("sign up success! please login!\n");
				continue;		
			case 3:
				//exit
				exit(-1);
				break;
			default:
				printf("parameter error!\n");
				continue;
		}
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
