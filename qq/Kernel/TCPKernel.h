#pragma once
#include"IKernel.h"
#include"TCPNet.h"
class TCPKernel :public IKernel
{
public:
	TCPKernel();
	virtual ~TCPKernel();
public:
	 bool Open();
	 void Close();
	 bool SendData(char* szbuf,int nLen);
	 void DealData(char* szbuf);
private:
	INet* m_pNet;

};