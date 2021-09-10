// DlgChat.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "qq.h"
#include "DlgChat.h"
#include "afxdialogex.h"
#include "packdef.h"
#include "DlgMain.h"

// CDlgChat �Ի���

IMPLEMENT_DYNAMIC(CDlgChat, CDialogEx)

CDlgChat::CDlgChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgChat::IDD, pParent)
	, m_edtSend(_T(""))
{

}

CDlgChat::~CDlgChat()
{
}

void CDlgChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstbox);
	DDX_Text(pDX, IDC_EDIT1, m_edtSend);
}


BEGIN_MESSAGE_MAP(CDlgChat, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgChat::OnBnClickedButton1)
END_MESSAGE_MAP()


// CDlgChat ��Ϣ�������


void CDlgChat::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//1.��ȡ����QQ
	CString strQQ;
	GetWindowText(strQQ);//��ȡ����(QQ��)
	//2.��ȡ��������
	UpdateData(TRUE);
	//3.����
	STRU_SELECTFRIENDCHAT_RQ ssr;
	ssr.m_nType=_DEF_PROTOCOL_SELECTFRIENDCHAT_RQ;
	ssr.m_friendqq=_atoi64(strQQ);
	ssr.m_qq=((CDlgMain*)theApp.m_pMainWnd)->m_qq;
	strcpy_s(ssr.m_szContent,DEFCONTENTNUM,m_edtSend);

	if(theApp.m_kernel.SendData((char*)&ssr,sizeof(ssr)))
	{
		m_lstbox.AddString("��˵:");
		m_lstbox.AddString(m_edtSend);
		m_edtSend="";
		UpdateData(FALSE);
	}
}
