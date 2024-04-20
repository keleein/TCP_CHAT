#include <stdio.h>
#include <pthread.h>
#include "thread.h"

void read_info(void *arg)
{
	int client = *(int*)arg;
	char buf[REDABUF] = {0};
	while(1)
	{
		int ret = recv(client,buf,sizeof(buf),0);
		if(ret < 0)
		{
			perror("recv");
			exit(-1);
		}else if(ret == 0)
		{
			printf("server disconnect!\n");
			continue;
		}else{
			printf("%s\n",buf);
			memset(buf,0,sizeof(buf));
		}
	}
}
