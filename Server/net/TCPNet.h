#pragma once
#include"INet.h"
#include"IKernel.h"
class TCPNet :public INet
{
public:
	TCPNet(IKernel *pKernel);
	~TCPNet(void);
public:
	bool InitNetWork();
	void UnInitNetWork();
    bool SendData(SOCKET sockWaiter,char* szbuf,int nLen);
	void RecvData(SOCKET sockWaiter);
public:
   static DWORD WINAPI ThreadProc( LPVOID lpParameter);

   static DWORD WINAPI ThreadRecv( LPVOID lpParameter);
private:
	SOCKET m_sockListen;
	std::list<HANDLE> m_lstThread;
	std::map<ULONG,SOCKET> m_mapThreadIdToSocket;
	bool  m_bFlagQuit;
	IKernel *m_pKernel;
};

