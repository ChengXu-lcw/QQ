#include "TCPNet.h"


TCPNet::TCPNet(IKernel *pKernel)
{
	m_sockListen = NULL;
	m_bFlagQuit = true;
	m_pKernel=pKernel;
}


TCPNet::~TCPNet(void)
{
}

bool TCPNet::InitNetWork()
{
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

/* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        /* Tell the user that we could not find a usable */
        /* Winsock DLL.                                  */
        printf("WSAStartup failed with error: %d\n", err);
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
        printf("Could not find a usable version of Winsock.dll\n");
        UnInitNetWork();
        return false;
    }
    else
        printf("The Winsock 2.2 dll was found okay\n");

	//2.雇个店长--
	m_sockListen = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP );
	if(m_sockListen == INVALID_SOCKET )
	{
		 UnInitNetWork();
        return false;
	}
	//3.找地（）--
	sockaddr_in  addrServer;
	addrServer.sin_family =AF_INET;
	addrServer.sin_addr.S_un.S_addr = 0;
	addrServer.sin_port = htons(8899);
	if(SOCKET_ERROR == bind(m_sockListen,(const sockaddr*)&addrServer,sizeof(sockaddr_in)))
	{
		UnInitNetWork();
        return false;
	}
	//4.宣传--listen(); 一旦开始监听，一直处于监听状态
	if(SOCKET_ERROR  == listen(m_sockListen,10))
	{
		UnInitNetWork();
        return false;
	}
	//接收连接--线程-
	HANDLE hThread = CreateThread(0,0,&ThreadProc,this,0,0);
	if(hThread)
		m_lstThread.push_back(hThread);
	return true;
}

DWORD WINAPI TCPNet::ThreadProc( LPVOID lpParameter)
{
	TCPNet *pthis = (TCPNet*)lpParameter;
	ULONG ThreadId;
	while(pthis->m_bFlagQuit)
	{
		SOCKET sockWaiter =  accept(pthis->m_sockListen,0,0);
		HANDLE hThread = CreateThread(0,0,&ThreadRecv,pthis,0,&ThreadId);
		if(hThread)
		{
			pthis->m_mapThreadIdToSocket[ThreadId] = sockWaiter;
			pthis->m_lstThread.push_back(hThread);
		}
			
	}
	return 0;
}

DWORD WINAPI TCPNet::ThreadRecv( LPVOID lpParameter)
{
	TCPNet *pthis = (TCPNet*)lpParameter;
	SOCKET sockWaiter = pthis->m_mapThreadIdToSocket[GetCurrentThreadId()];
	pthis->RecvData(sockWaiter);
	return 0;
}
void TCPNet::UnInitNetWork()
{
	m_bFlagQuit  =false;
	auto ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{
		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
			TerminateThread(*ite,-1);

		CloseHandle(*ite);
		*ite = NULL;
		ite++;
	}
	if(m_sockListen)
	{
		closesocket(m_sockListen);
		m_sockListen = NULL;
	}
    WSACleanup();
}
bool TCPNet::SendData(SOCKET sockWaiter,char* szbuf,int nLen)
{
	if(!sockWaiter || !szbuf || nLen <0)
		return false;
	if(send(sockWaiter,(const char*)&nLen,sizeof(int),0) <=0)
		return false;

	if(send(sockWaiter,szbuf,nLen,0) <=0)
		return false;

	return true;
}

void TCPNet::RecvData(SOCKET sockWaiter)
{
	int nPackSize;
	char*pszbuf = NULL;
	while(m_bFlagQuit)
	{
		//接收包大小
		int nRelReadNum = recv(sockWaiter,(char*)&nPackSize,sizeof(int),0);
	
		if(nRelReadNum <0)
		{
			if(GetLastError() == 10054)
			{
				auto ite = m_mapThreadIdToSocket.begin();
				while(ite != m_mapThreadIdToSocket.end())
				{
					if(sockWaiter == ite->first)
					{
						closesocket(sockWaiter);
						m_mapThreadIdToSocket.erase(ite);
						return ;
					}
					ite++;
				}
			}
			continue;
		}
			
	    //接收数据包
		pszbuf =new char[nPackSize];
		int noffset =0;
		while(nPackSize)
		{
			nRelReadNum = recv(sockWaiter,pszbuf+noffset,nPackSize,0);
			noffset+= nRelReadNum;
			nPackSize -= nRelReadNum;
		}
		
		//处理
		//cout<<pszbuf<<endl;
		m_pKernel->DealData(pszbuf,sockWaiter);
		delete []pszbuf;
		pszbuf= NULL;

	}
}