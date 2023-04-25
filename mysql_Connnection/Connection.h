#pragma once
#include<mysql.h>
#include<iostream>
#include"public.h"
using namespace std;
#include<string>
#include <ctime>
/*
	mysql数据库的增删改查
*/

class Connection {
public:
	// 初始化数据库连接
	Connection();
	// 释放数据库连接资源
	~Connection();
	bool connect(string ip,
		unsigned short port,
		string user,
		string password,
		string dbname);
	// 更新操作 insert、delete、update
	bool update(string sql);
	// 查询操作 select
	MYSQL_RES* query(string sql);

	// 刷新一下连接的起始的空闲时间点
	void refreshAliveTime() {
		_alivetime = clock();
	}

	//存活时间
	clock_t getAliveTime() const{ return _alivetime - clock(); }
private:
	MYSQL* _conn;
	clock_t _alivetime;   //在队列中的时间点
};