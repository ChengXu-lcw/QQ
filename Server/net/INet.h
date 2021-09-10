#pragma once
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <list>
#include <map>
// Need to link with Ws2_32.lib
#pragma comment(lib, "ws2_32.lib")
class INet
{
public:
	INet()
	{


	}
	virtual ~INet()
	{



	}
public:
	virtual bool InitNetWork()=0;
	virtual void UnInitNetWork()=0;
    virtual bool SendData(SOCKET sockWaiter,char* szbuf,int nLen)=0;
	virtual void RecvData(SOCKET sockWaiter)=0;



};