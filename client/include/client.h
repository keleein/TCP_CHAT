#ifndef _CLIENT_H_
#define _CLIENT_H_

#define SERVER_ADDR "123.57.79.219"
#define SERVER_PORT 5555
#define READBUF 64

typedef struct Account{
	int info_type;	//消息类型：1登陆消息，2注册消息，3广播消息，4组播消息
	char nickname[32];
	char passwd[32];
}account;

struct Account login_account;

void read_info(void *arg);

int client_init();

#endif
