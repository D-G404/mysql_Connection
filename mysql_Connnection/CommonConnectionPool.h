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
	���ӳ�ģ��
*/
class ConnectionPool {
public:
	static ConnectionPool* getConnectionPool();
	shared_ptr<Connection> getConnection();
private:
	ConnectionPool();

	string _ip; // mysql��ip��ַ
	unsigned short _port; // mysql�Ķ˿ں� 3306
	string _username; // mysql��¼�û���
	string _password; // mysql��¼����
	string _dbname; // ���ӵ����ݿ�����
	int _initSize; // ���ӳصĳ�ʼ������
	int _maxSize; // ���ӳص����������
	int _maxIdleTime; // ���ӳ�������ʱ��
	int _connectionTimeout; // ���ӳػ�ȡ���ӵĳ�ʱʱ��
	atomic_int _connectionCnt; //��������
	queue<Connection*>_connectionQue; //���Ӷ���
	mutex _queueMutex;	//����ά���̰߳�ȫ
	condition_variable cv; //��������

	bool loadConfigFile(); //���������ļ�

	void produceConnectionTask();//�����߸�������
	
	void scannerConnectionTask();// ɨ�賬��maxIdleTimeʱ��Ŀ������ӣ����ж��ڵ����ӻ���


	
};