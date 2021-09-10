#pragma once
#include"INet.h"

class TCPNet :public INet
{
public:
	TCPNet();
	virtual ~TCPNet();
public:
	 bool InitNetWork();
	 void UnInitNetWork();
	 bool SendData(char* szbuf,int nLen);
	 void RecvData();
public:
	static DWORD WINAPI ThreadProc(LPVOID lpParameter);//�̺߳���Ҫͨ��������������ֱ�����ҵõ�
private:
	SOCKET m_sockClient;
	HANDLE m_hThread;
	bool m_bFlagQuit;



};