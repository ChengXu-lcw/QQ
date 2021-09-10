#include "stdafx.h"
#include"TCPKernel.h"
#include"packdef.h"
#include"qq.h"
 TCPKernel::TCPKernel()
{
		m_pNet=new TCPNet;
}
 TCPKernel::~TCPKernel()
{
		delete m_pNet;
		m_pNet=NULL;
}

bool TCPKernel::Open()
{
	if(!m_pNet->InitNetWork())
		return false;

	return true;
}
void TCPKernel::Close()
{
	m_pNet->UnInitNetWork();
}
bool TCPKernel::SendData(char* szbuf,int nLen)
{
	if(!m_pNet->SendData(szbuf,nLen))
		return false;

	return true;

}
void TCPKernel::DealData(char* szbuf)
{
	//todo
	switch (*szbuf)
	{
	case _DEF_PROTOCOL_REGISTER_RS:
		{
			STRU_REGISTER_RS *psrr =(STRU_REGISTER_RS *)szbuf;
			if(psrr->m_qq)
			{
				AfxMessageBox(_T("ע��ɹ���"));
				theApp.m_pMainWnd->SendMessage(UM_REGISTERMSG,(WPARAM)&psrr->m_qq);
			}
			else
				AfxMessageBox(_T("ע��ʧ�ܣ��㲻��ӵ��һ��QQ�ţ�"));
		}
		break;
	case _DEF_PROTOCOL_LOGIN_RS:
		{
			STRU_LOGIN_RS *pslr =(STRU_LOGIN_RS *)szbuf;
			char *pszResult=NULL;
			 /*_login_success 0
			 _login_error 1
			 _login_nouser 2*/
			if(pslr->m_szResult==_login_error)
              pszResult="_login_error";
			else if(pslr->m_szResult==_login_nouser)
              pszResult="_login_nouser";
			else
			{
				//��½�ɹ�
				theApp.m_pMainWnd->PostMessage(UM_LOGINMSG);//�˴�����ʹ��PostMessage()������SendMessage(),��������
                return;
			}
			AfxMessageBox(pszResult);
		}
		break;
	case _DEF_PROTOCOL_GETFRIENDLIST_RS:
		{
		//��������Ϣ���͵��µĴ���
		STRU_GETFRIENDLIST_RS *psgr=(STRU_GETFRIENDLIST_RS *)szbuf;
		theApp.m_pMainWnd->SendMessage(UM_GETFRIENDLISTMSG,(WPARAM)psgr->m_aryInfo,psgr->m_nNum);
		}
		break;
    case _DEF_PROTOCOL_SELECTFRIENDCHAT_RQ:
		{
		
		STRU_SELECTFRIENDCHAT_RQ *pssr=(STRU_SELECTFRIENDCHAT_RQ *)szbuf;
		theApp.m_pMainWnd->SendMessage(UM_CHATMSG,(WPARAM)&pssr->m_qq,(LPARAM)pssr->m_szContent);
		}
		break;
	default:
		break;
	}


}



