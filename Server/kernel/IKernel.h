#pragma once
#include"INet.h"

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
   virtual bool Open() = 0;
   virtual void Close() = 0;
   virtual void DealData(char *szbuf,SOCKET sockWaiter) = 0;

};