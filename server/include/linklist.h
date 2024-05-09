#ifndef _LINKLIST_H_
#define _LINKLIST_H_

#define NICKNAME 32

typedef struct Client_info{
	int connfd;	//连接套接字
	struct sockaddr_in client_addr;	//IP PORT family
	char nickname[NICKNAME];	//昵称
	struct Client_info *next;
}client_info;

client_info *list_init();

void insert(client_info *head,int connfd,const char *ip,unsigned short port);

void node_delete(client_info *head,int connfd);

void modify_nickname(client_info *head,int connfd,char *nickname);

#endif
