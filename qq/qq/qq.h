
// qq.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "TCPKernel.h"

// CMyqqApp:
// �йش����ʵ�֣������ qq.cpp
//

class CMyqqApp : public CWinApp
{
public:
	CMyqqApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
public:
	TCPKernel m_kernel;
	virtual int ExitInstance();
};

extern CMyqqApp theApp;