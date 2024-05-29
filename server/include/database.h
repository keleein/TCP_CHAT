#ifndef _DATABASE_C_
#define _DATABASE_C_

#include <sqlite3.h>

//用户信息
typedef struct {
	unsigned short id;
	char nickname[32];
	char passwd[32];
}Usrinfo;

//基本操作：打开数据库
sqlite3 *open_database(const char *pathname);

//基本操作：执行sql语句
int exec_database(sqlite3 *data,char *sql);

//基本操作：获取用户表
int get_data_base(sqlite3 *data,char *sql,char **res,int *row,int *col);

//基本操作：关闭数据库
int close_database(sqlite3 *data);

//复合操作：添加用户信息
int data_user_add(sqlite3 *db,Usrinfo data_usr);

//复合操作：删除用户信息
int data_user_del(sqlite3 *db,unsigned short id);
#endif
