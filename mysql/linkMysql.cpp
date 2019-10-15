// linkRedis.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
//#include <iostream>
#include <string>
//#include <vector>
#include <mysql.h>




int main()
{
	MYSQL *con;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char sql[256];

	char dbuser[30] = "root";
	char dbpasswd[30] = "qwer1234"; // it must be    changed
	char dbip[30] = "localhost";
	char dbname[50] = "test";
	char tablename[50] = "employer";
	char query[] = "set names \'GBK\'";

	int x;
	int y;
	int rt;
	unsigned int t;
	int count = 0;

	con = mysql_init((MYSQL*)0);
	if (con != NULL && mysql_real_connect(con, dbip, dbuser, dbpasswd, dbname, 3306, NULL, 0)) {
		if (!mysql_select_db(con, dbname)) {
			printf("Select successfully the database!\n");
			con->reconnect = 1;
						
			rt = mysql_real_query(con, query, strlen(query));
			if (rt) {
				printf("Error making query: %s !!!\n", mysql_error(con));
			}
			else {
				printf("query %s succeed!\n", query);
			}
		}
	}
	else {
		MessageBoxA(NULL, "Unable to connect the database,check your configuration!", "", NULL);
	}
	//sprintf(tmp, "insert into %s values(%s,%d,%d)", tablename, "null", x, y); //注意如何向具有自增字段的数据库中插入记录
	sprintf_s(sql, "insert into employer values(null,'li','200')");

	//增
	rt = mysql_real_query(con, sql, strlen(sql));
	if (rt)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", sql);
	}

	sprintf_s(sql, "select * from %s", tablename);
	rt = mysql_real_query(con, sql, strlen(sql));
	if (rt)
	{
		printf("Error making query: %s !!!\n", mysql_error(con));
	}
	else
	{
		printf("%s executed!!!\n", sql);
	}
	res = mysql_store_result(con);//将结果保存在res结构体中


	//查
	while (row = mysql_fetch_row(res)) {
		for (t = 0; t < mysql_num_fields(res); t++) {
			printf("%s  ", row[t]);
		}
		printf(".............\n");
		count++;
	}

	printf("number of rows %d\n", count);
	printf("mysql_free_result...\n");
	mysql_free_result(res);
	mysql_close(con);
	system("pause");

}


