#pragma once
#include "afxcmn.h"

#include "DlgChat.h"
#include <map>
// CDlgMain �Ի���

class CDlgMain : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgMain();

// �Ի�������
	enum { IDD = IDD_DLG_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	LRESULT  GetFriendListMsg(WPARAM W,LPARAM L); //��ӻ�ȡ����������Ϣ
	LRESULT  SelectFriendChatMsg(WPARAM W,LPARAM L); //��ӽ��պ�����Ϣ
	DECLARE_MESSAGE_MAP()
public:
	long long m_qq;//������¼��ǰQQ��
	CListCtrl m_lstctrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
    std::map<CString,CDlgChat*> m_mapQQToDlg;

};
