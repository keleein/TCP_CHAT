#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "linklist.h"

//初始化信息链表
client_info *list_init()
{
	client_info *head = (client_info*)malloc(sizeof(client_info));
	head->connfd = -1;
	head->client_addr.sin_family = AF_INET;
	head->client_addr.sin_port = htons(5555);
	head->client_addr.sin_addr.s_addr = inet_addr("0");
	memset(head->nickname,0,NICKNAME);
	head->next = NULL;
	return head;
}

//插入客户端信息
void insert(client_info *head,int connfd,const char *ip,unsigned short port)
{
	client_info *new = (client_info*)malloc(sizeof(client_info));
	new->connfd = connfd;
	new->client_addr.sin_family = AF_INET;
	new->client_addr.sin_addr.s_addr = inet_addr(ip);
	new->client_addr.sin_port = htons(port);
	strcpy(new->nickname,"NULL");

	//头插法
	new->next = head->next;
	head->next = new;
}

//删除指定客户端
void node_delete(client_info *head,int connfd)
{
	if(head->next != NULL)
	{
		printf("delete error : list is empty!\n");
		exit(-1);
	}else{
		client_info *tmp = head;
		client_info *p = head->next;
		while(p != NULL)
		{
			if(p->connfd == connfd)
				break;
			tmp = tmp->next;
			p = p->next;
		}
		if(p == NULL)
		{
			printf("delete error : not found!\n");
			exit(-1);
		}else{
			tmp->next = p->next;
			free(p);
		}
	}
}

//修改客户端昵称
void modify_nickname(client_info *head,int connfd,char *nickname)
{
	client_info *p = head->next;
	while(p != NULL)
	{
		if(p->connfd == connfd)
			break;
		p = p->next;
	}
	if(p != NULL)
	{
		strcpy(p->nickname,nickname);
	}else{
		printf("modify_nickname error : not found!\n");
		exit(-1);
	}
}
