#pragma once
#include "afxcmn.h"

#include "DlgChat.h"
#include <map>
// CDlgMain 对话框

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMain();

// 对话框数据
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	LRESULT  GetFriendListMsg(WPARAM W,LPARAM L); //添加获取好友链表消息
	LRESULT  SelectFriendChatMsg(WPARAM W,LPARAM L); //添加接收好友消息
	DECLARE_MESSAGE_MAP()
public:
	long long m_qq;//用来记录当前QQ号
	CListCtrl m_lstctrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    std::map<CString,CDlgChat*> m_mapQQToDlg;

};
