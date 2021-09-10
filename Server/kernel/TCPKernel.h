#pragma once
#include"IKernel.h"//winsock2.h(无判断)
#include"CMySql.h"//winsock.h (有判断，防止多重定义)
#include"packdef.h"
#include <map>
class TCPKernel;
typedef void (TCPKernel::*PFUN)(char *,SOCKET );

struct ProtocolMap
{
	char m_ntype;//协议
	PFUN m_pfun;//函数地址

};
class TCPKernel:public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
   virtual bool Open();
   virtual void Close();
   virtual void DealData(char *szbuf,SOCKET sockWaiter);
public:
	void RegisterRq(char *szbuf,SOCKET sockWaiter);
	void LoginRq(char *szbuf,SOCKET sockWaiter);
	void GetFriendListRq(char *szbuf,SOCKET sockWaiter);
	void SelectFriendChatRq(char *szbuf,SOCKET sockWaiter);
	void KeepAlive(char *szbuf,SOCKET sockWaiter);
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);
public:
	INet *m_pNet;
	CMySql m_sql;
	std::map<long long,SOCKET> m_mapQQToSocket;
	std::map<SOCKET,DWORD> m_mapSocketToTime;
	HANDLE a;


	
};