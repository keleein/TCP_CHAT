#ifndef _DATA_FUNC_C_
#define _DATA_FUNC_C_

#include <sqlite3.h>

sqlite3 *open_database(const char *pathname);

int exec_database(sqlite3 *data,char *sql);

int get_data_base(sqlite3 *data,char *sql,char **res,int *row,int *col);

int close_database(sqlite3 *data);

#endif
