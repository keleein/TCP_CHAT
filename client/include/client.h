#ifndef _CLIENT_H_
#define _CLIENT_H_

#define SERVER_ADDR "123.57.79.219"
#define SERVER_PORT 5555
#define READBUF 64

//账户信息结构体
typedef struct Account{
	int info_type;	//消息类型：1登陆消息，2注册消息
	int user_id;
	char nickname[32];
	char passwd[32];
}account;

//群聊信息结构体
typedef struct Group{
	int info_type;  //消息类型：1服务器群聊，2分组群聊列表
	int group_id;
	char group_name[32];
}group;

//当前登录账号信息结构体
struct Account login_account;

//在线群聊信息数组
#define READY_GROUP 50

//功能函数
void read_info(void *arg);

int client_init();

#endif
