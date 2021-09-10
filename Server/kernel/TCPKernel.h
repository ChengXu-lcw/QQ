#pragma once
#include"IKernel.h"//winsock2.h(���ж�)
#include"CMySql.h"//winsock.h (���жϣ���ֹ���ض���)
#include"packdef.h"
#include <map>
class TCPKernel;
typedef void (TCPKernel::*PFUN)(char *,SOCKET );

struct ProtocolMap
{
	char m_ntype;//Э��
	PFUN m_pfun;//������ַ

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