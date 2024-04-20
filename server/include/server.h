#ifndef _SERVER_INIT_
#define _SERVER_INIT_

#define PORT 5555	//server port

int server_init();

int client_disconnect(int epfd,client_info *head,int connfd);

#endif
