#include "stdafx.h"
#include"TCPNet.h"
#include"packdef.h"
#include "qq.h"

TCPNet::TCPNet()
{
		m_sockClient=NULL;
		m_hThread=0;
	    m_bFlagQuit=true;
}
TCPNet::~TCPNet()
{

}

bool TCPNet::InitNetWork()
{
		 //1.���ؿ�WSAStartup();
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        
        return false;
        }

/* Confirm that the WinSock DLL supports 2.2.*/
/* Note that if the DLL supports versions greater    */
/* than 2.2 in addition to 2.2, it will still return */
/* 2.2 in wVersion since that is the version we      */
/* requested.                                        */

    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
        /* Tell the user that we could not find a usable */
        /* WinSock DLL.                                  */
        
        UnInitNetWork();
        return false;
   }
    

	//2.�����׽��� socket();
	m_sockClient=socket(AF_INET ,SOCK_STREAM ,IPPROTO_TCP );
	if(m_sockClient==INVALID_SOCKET)
	{
		UnInitNetWork();
        return false;
	}
	//3.���ӷ�����connect();���ӵ�ָ�����׽���
	sockaddr_in addServer;
	addServer.sin_family=AF_INET;
	/*addServer.sin_addr.S_un.S_addr=0;*/
	InetPtonA(AF_INET,SERVERIP,&addServer.sin_addr);
	addServer.sin_port=htons(8899);
	
	if(SOCKET_ERROR==connect(m_sockClient,(const sockaddr *)&addServer,sizeof(addServer)))
	{
		UnInitNetWork();
        return false;
	}
	//recv--�߳���
	m_hThread=CreateThread(0,0,&ThreadProc,this,0,0);
	return true;
}


DWORD WINAPI TCPNet::ThreadProc(LPVOID lpParameter)
{
		 TCPNet *pthis = (TCPNet *)lpParameter;
		 pthis->RecvData();
		 
		 return 0;
}




void TCPNet::UnInitNetWork()
{
		 //�̵߳�����
		 m_bFlagQuit=false;
		 if(m_hThread)
		 {
			 if(WAIT_TIMEOUT==WaitForSingleObject(m_hThread,100))
				 TerminateThread(m_hThread,-1);
			 //�رվ��
			 CloseHandle(m_hThread);
			 m_hThread=NULL;
		 }
		 //�ر��׽���
		 if(m_sockClient)
		 {
			 closesocket(m_sockClient);
			 m_sockClient=NULL;
		 }
		 //����
		 WSACleanup();
}

bool TCPNet::SendData(char* szbuf,int nLen)
{
		 //�ȷ������ݰ��Ĵ�С���ٷ�������
		 if( !szbuf || nLen <0)
		return false;
	if(send(m_sockClient,(const char*)&nLen,sizeof(int),0) <=0)
		return false;

	if(send(m_sockClient,szbuf,nLen,0) <=0)
		return false;

	return true;
}

void TCPNet::RecvData()
{	
	int nPackSize;
	char*pszbuf = NULL;
	while(m_bFlagQuit)
	{
		//���հ���С
		int nRelReadNum = recv(m_sockClient,(char*)&nPackSize,sizeof(int),0);
	
		if(nRelReadNum <0)
		{
			continue;
		}
			
	    //�������ݰ�
		pszbuf =new char[nPackSize];
		int noffset =0;
		while(nPackSize)
		{
			nRelReadNum = recv(m_sockClient,pszbuf+noffset,nPackSize,0);
			noffset+= nRelReadNum;
			nPackSize -= nRelReadNum;
		}
		
		//����
		//cout<<pszbuf<<endl;
		//m_pKernel->DealData(pszbuf,sockWaiter);
		theApp.m_kernel.DealData(pszbuf);
		delete []pszbuf;
		pszbuf= NULL;

	 }
}
