// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "qq.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "packdef.h"


// CDlgMain 对话框

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
	//消息映射(获取好友列表)
	ON_MESSAGE(UM_GETFRIENDLISTMSG,&CDlgMain::GetFriendListMsg)
	ON_MESSAGE(UM_CHATMSG,&CDlgMain::SelectFriendChatMsg)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CDlgMain::OnNMDblclkList1)
END_MESSAGE_MAP()

LRESULT  CDlgMain::SelectFriendChatMsg(WPARAM W,LPARAM L)
{
	//long long*qq=(long long*)W;
	long long qq= *(long long*)W;//两种写法都可
	char *szbuf=(char *)L;
	CString strqq;
	strqq.Format("%lld",qq);
	//如果没有聊天窗口，创建聊天窗口
	CDlgChat *pdlg= m_mapQQToDlg[strqq];
	//2.弹出聊天窗口
	//如果之前没有过窗口，则创建窗口
	if(!pdlg)
	{
	pdlg=new CDlgChat;//窗口选择为非模态对话框
	pdlg->Create(IDD_DLG_CHAT);
	pdlg->SetWindowTextA(strqq);
	m_mapQQToDlg[strqq]=pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);
	strqq += "说:";
	pdlg->m_lstbox.AddString(strqq);
	pdlg->m_lstbox.AddString(szbuf);
	return 0;
}
// CDlgMain 消息处理程序
LRESULT  CDlgMain::GetFriendListMsg(WPARAM W,LPARAM L)
{
	FriendInfo *pInfo=(FriendInfo *)W;
	CString str;
	for(long i=0;i<L;i++)
	{
		//第0列：QQ号
		str.Format("%lld",pInfo[i].m_qq);
		m_lstctrl.InsertItem(i,str);
		//第1列：name
		m_lstctrl.SetItemText(i,1,pInfo[i].m_szName);
		//第2列：在线状态
		str.Format("%c",pInfo[i].m_szState);
		m_lstctrl.SetItemText(i,2,str);

	}
	return 0;
}

BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//初始化listctrl
	m_lstctrl.InsertColumn(0,"QQ号",0,100);//参数：第几列,列标题,对齐方式,列宽
	m_lstctrl.InsertColumn(1,"昵称",0,100);
	m_lstctrl.InsertColumn(2,"状态",0,100);
	m_lstctrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);//好友列表风格：整行选中
	//发送获取好友列表请求
	STRU_GETFRIENDLIST_RQ sgr;
	sgr.m_nType=_DEF_PROTOCOL_GETFRIENDLIST_RQ;
	sgr.m_qq=m_qq;

	theApp.m_kernel.SendData((char*)&sgr,sizeof(sgr));
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CDlgMain::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	
	// TODO: 在此添加控件通知处理程序代码

	*pResult = 0;
	if(pNMItemActivate->iItem==-1)
	  return;
	//1.获取双击好友QQ
	CString strqq = m_lstctrl.GetItemText(pNMItemActivate->iItem,0);//获得指定项的内容函数
	//如果之前有过窗口，直接弹出，否则创建窗口
	CDlgChat *pdlg= m_mapQQToDlg[strqq];
	//2.弹出聊天窗口
	//如果之前没有过窗口，则创建窗口
	if(!pdlg)
	{
	pdlg=new CDlgChat;//窗口选择为非模态对话框
	pdlg->Create(IDD_DLG_CHAT);
	pdlg->SetWindowTextA(strqq);
	m_mapQQToDlg[strqq]=pdlg;
	}
	pdlg->ShowWindow(SW_SHOW);//无论哪种情况都要将对话框显示出来
}
