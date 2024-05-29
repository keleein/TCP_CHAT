#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <unistd.h>
#include "database.h"

//基本操作：打开数据库
sqlite3 *open_database(const char *pathname)
{
	sqlite3 *db;
	int ret = sqlite3_open(pathname,&db);
	if(ret != SQLITE_OK)
	{
		perror("open_database: sqlite3_open");
		exit(-1);
	}
	return db;
}

//基本操作：执行sql语句
int exec_database(sqlite3 *data,char *sql)
{
	char *errmsg;
	int ret = sqlite3_exec(data,sql,NULL,NULL,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("exec_database: sqlite3_exec: %s\n",errmsg);
		return -1;
	}
	sqlite3_free(errmsg);
	return 0;	//exec success
}

//基本操作：获取数据表
int get_database(sqlite3 *data,char *sql,char **res,int *row,int *col)
{
	char *errmsg;
	int ret = sqlite3_get_table(data,sql,&res,row,col,&errmsg);
	if(ret != SQLITE_OK)
	{
		printf("get_database: sqlite3_get_tables: %s\n",errmsg);
		return -1;
	}
	sqlite3_free(errmsg);
	return 0;	//get success
}

//基本操作：关闭数据库
int close_database(sqlite3 *data)
{
	int ret = sqlite3_close(data);
	if(ret != SQLITE_OK)
	{
		printf("close_database: sqlite3_close: error!\n");
		return -1;
	}
	return 0;
}

//复合操作：增加用户信息
int data_user_add(sqlite3 *db,Usrinfo data_usr)
{
	char sql[128] = "0";
	sprintf(sql,"insert into user values (%d,'%s','%s');",data_usr.id,data_usr.nickname,data_usr.passwd);
	if(exec_database(db,sql) != 0)
	{
		printf("data_user_add : exec_database error!");
		return -1;
	}
	return 0;
}

//复合操作：删除用户信息
int data_user_del(sqlite3 *db,unsigned short id)
{
	char sql[128] = "0";
	sprintf(sql,"delete from user where id=%d;",id);
	if(exec_database(db,sql) != 0)
        {
                printf("data_user_del: exec_database error!");
                return -1;
        }
        return 0;
}
