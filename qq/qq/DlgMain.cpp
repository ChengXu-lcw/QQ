// DlgMain.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "qq.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "packdef.h"


// CDlgMain �Ի���

IMPLEMENT_DYNAMIC(CDlgMain, CDialogEx)

CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{

}

CDlgMain::~CDlgMain()
{
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_lstctrl);
}


BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	//��Ϣӳ��(��ȡ�����б�)
	ON_MESSAGE(UM_GETFRIENDLISTMSG,&CDlgMain::GetFriendListMsg)
	ON_MESSAGE(UM_CHATMSG,&CDlgMain::SelectFriendChatMsg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDlgMain::OnNMDblclkList1)
END_MESSAGE_MAP()

LRESULT  CDlgMain::SelectFriendChatMsg(WPARAM W,LPARAM L)
{
	//long long*qq=(long long*)W;
	long long qq= *(long long*)W;//����д������
	char *szbuf=(char *)L;
	CString strqq;
	strqq.Format("%lld",qq);
	//���û�����촰�ڣ��������촰��
	CDlgChat *pdlg= m_mapQQToDlg[strqq];
	//2.�������촰��
	//���֮ǰû�й����ڣ��򴴽�����
	if(!pdlg)
	{
	pdlg=new CDlgChat;//����ѡ��Ϊ��ģ̬�Ի���
	pdlg->Create(IDD_DLG_CHAT);
	pdlg->SetWindowTextA(strqq);
	m_mapQQToDlg[strqq]=pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);
	strqq += "˵:";
	pdlg->m_lstbox.AddString(strqq);
	pdlg->m_lstbox.AddString(szbuf);
	return 0;
}
// CDlgMain ��Ϣ�������
LRESULT  CDlgMain::GetFriendListMsg(WPARAM W,LPARAM L)
{
	FriendInfo *pInfo=(FriendInfo *)W;
	CString str;
	for(long i=0;i<L;i++)
	{
		//��0�У�QQ��
		str.Format("%lld",pInfo[i].m_qq);
		m_lstctrl.InsertItem(i,str);
		//��1�У�name
		m_lstctrl.SetItemText(i,1,pInfo[i].m_szName);
		//��2�У�����״̬
		str.Format("%c",pInfo[i].m_szState);
		m_lstctrl.SetItemText(i,2,str);

	}
	return 0;
}

BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//��ʼ��listctrl
	m_lstctrl.InsertColumn(0,"QQ��",0,100);//�������ڼ���,�б���,���뷽ʽ,�п�
	m_lstctrl.InsertColumn(1,"�ǳ�",0,100);
	m_lstctrl.InsertColumn(2,"״̬",0,100);
	m_lstctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);//�����б�������ѡ��
	//���ͻ�ȡ�����б�����
	STRU_GETFRIENDLIST_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETFRIENDLIST_RQ;
	sgr.m_qq=m_qq;

	theApp.m_kernel.SendData((char*)&sgr,sizeof(sgr));
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgMain::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	*pResult = 0;
	if(pNMItemActivate->iItem==-1)
	  return;
	//1.��ȡ˫������QQ
	CString strqq = m_lstctrl.GetItemText(pNMItemActivate->iItem,0);//���ָ��������ݺ���
	//���֮ǰ�й����ڣ�ֱ�ӵ��������򴴽�����
	CDlgChat *pdlg= m_mapQQToDlg[strqq];
	//2.�������촰��
	//���֮ǰû�й����ڣ��򴴽�����
	if(!pdlg)
	{
	pdlg=new CDlgChat;//����ѡ��Ϊ��ģ̬�Ի���
	pdlg->Create(IDD_DLG_CHAT);
	pdlg->SetWindowTextA(strqq);
	m_mapQQToDlg[strqq]=pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);//�������������Ҫ���Ի�����ʾ����
}
