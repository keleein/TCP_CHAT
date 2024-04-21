#include <stdio.h>
#include <pthread.h>
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

//登录逻辑
int login()
{
	//输入登录信息
	account a1;
	a1.info_type = 1;
	printf("please input login infomation:\n");
	printf("nickname:");
	scanf("%s",a1.nickname);
	printf("passwd:");
	scanf("%s",a1.passwd);

	//与服务器建立连接
	int loginfd = client_init();
	if(loginfd < 0)
	{
		perror("login_client_init");
		exit(-1);
	}

	//上传登录信息
	int ret = send(loginfd,&a1,sizeof(a1),0);
	if(ret < 0)
	{
		perror("login_send");
		exit(-1);
	}

	//接收服务器反馈
	char buf[32] = {0};
	ret = recv(loginfd,buf,sizeof(buf),0);
	if(ret < 0)
	{
		perror("login_recv");
		exit(-1);
	}

	//判断反馈情况
	int jud = strcmp(buf,"OK");
	if(jud == 0)
	{
		//登陆成功
		login_account = a1;
		return loginfd;
	}else{
		//登陆失败
		close(loginfd);
		return -1;
	}
}

//注册逻辑
int signup()
{
	//输入注册信息
	account a1;
	a1.info_type = 2;
	printf("please input sign up infomation:\n");
	printf("nickname:");
	scanf("%s",a1.nickname);
	printf("passwd:");
	scanf("%s",a1.passwd);

	//建立服务器连接
	int signfd = client_init();
	if(sigfd < 0)
	{
		perror("sign_up_client_init");
		exit(-1);
	}

	//发送注册信息
	int ret = send(signfd,&a1,sizeof(a1),0);
	if(ret < 0)
	{
		perror("sign_up_send");
		exit(-1);
	}

	//接收服务器反馈信息
	char buf[32] = {0};
	ret = recv(signfd,buf,sizeof(buf),0);
	if(ret < 0)
	{
		perror("sign_up_recv");
		exit(-1);
	}

	//关闭注册连接
	close(signfd);

	//返回注册情况 0成功 -1失败
	return (strcmp(buf,"OK") == 0) ? 0 : -1;
}

//用户主页面
int homepage()
{
	while(1)
	{
		int jud = 0;
		printf("---------------当前用户：%s----------------",login_account.nickname);
		printf("---------------1.加入群聊-------------------");
		printf("---------------2.创建群聊-------------------");
		printf("---------------3.在线私聊-------------------");
		printf("---------------4.退出账号-------------------");
		scnaf("%d",jud);
		switch(jud)
		{
			case 1:
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				return 0;
			default:
				printf("parameter error!\n");
		}
	}
}

//线程函数：读取服务器消息
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
