#pragma once
#include<mysql.h>
#include<iostream>
#include"public.h"
using namespace std;
#include<string>
#include <ctime>
/*
	mysql���ݿ����ɾ�Ĳ�
*/

class Connection {
public:
	// ��ʼ�����ݿ�����
	Connection();
	// �ͷ����ݿ�������Դ
	~Connection();
	bool connect(string ip,
		unsigned short port,
		string user,
		string password,
		string dbname);
	// ���²��� insert��delete��update
	bool update(string sql);
	// ��ѯ���� select
	MYSQL_RES* query(string sql);

	// ˢ��һ�����ӵ���ʼ�Ŀ���ʱ���
	void refreshAliveTime() {
		_alivetime = clock();
	}

	//���ʱ��
	clock_t getAliveTime() const{ return _alivetime - clock(); }
private:
	MYSQL* _conn;
	clock_t _alivetime;   //�ڶ����е�ʱ���
};