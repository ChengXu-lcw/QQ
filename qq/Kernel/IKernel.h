#pragma once

class IKernel
{
public:
	IKernel()
	{

	}
	virtual ~IKernel()
	{

	}
public:
	virtual bool Open()=0;
	virtual void Close()=0;
	virtual bool SendData(char* szbuf,int nLen)=0;
	virtual void DealData(char* szbuf)=0;


};