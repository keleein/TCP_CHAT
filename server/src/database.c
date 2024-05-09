#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <unistd.h>
#include "database.h"

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
