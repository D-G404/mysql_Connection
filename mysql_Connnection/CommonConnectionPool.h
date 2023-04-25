#pragma once
#include<string>
#include<queue>
#include"Connection.h"
#include<mutex>
#include<atomic>
#include<stdlib.h>
#include<thread>
#include<functional>
#include<memory>
#include<condition_variable>

using namespace std;
/*
	连接池模块
*/
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();
	shared_ptr<Connection> getConnection();
private:
	ConnectionPool();

	string _ip; // mysql的ip地址
	unsigned short _port; // mysql的端口号 3306
	string _username; // mysql登录用户名
	string _password; // mysql登录密码
	string _dbname; // 连接的数据库名称
	int _initSize; // 连接池的初始连接量
	int _maxSize; // 连接池的最大连接量
	int _maxIdleTime; // 连接池最大空闲时间
	int _connectionTimeout; // 连接池获取连接的超时时间
	atomic_int _connectionCnt; //连接数量
	queue<Connection*>_connectionQue; //连接队列
	mutex _queueMutex;	//用来维护线程安全
	condition_variable cv; //条件变量

	bool loadConfigFile(); //加载配置文件

	void produceConnectionTask();//生产者负责生产
	
	void scannerConnectionTask();// 扫描超过maxIdleTime时间的空闲连接，进行对于的连接回收


	
};