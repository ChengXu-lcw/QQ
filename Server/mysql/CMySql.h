#pragma once
typedef unsigned long long  uint64_t;
#define MYSQL_ABI_CHECK
#include <mysql.h>
//#include <WinSock2.h>
#pragma comment(lib,"libmysql.lib")
//
#include <list>
using namespace std;

class CMySql
{
public:
    CMySql(void);
    ~CMySql(void);
public:                //ip, �û��������룬���ݿ� 
    bool  ConnectMySql(const char *host,const char *user,const char *pass,const char *db,short nport = 3306);
    void  DisConnect();   // 1  xiaoxiao  2  2 xiaonui null  3 xiao  5
    bool  SelectMySql(const char* szSql,int nColumn,list<string>& lstStr);
	//������ݿ��еı�
    bool GetTables(const char* szSql,list<string>& lstStr);
    //���£�ɾ�������롢�޸�
    bool  UpdateMySql(const char* szSql);
 
private:
    MYSQL *sock;   
	MYSQL_RES *results;   
	MYSQL_ROW record; 
   
};

