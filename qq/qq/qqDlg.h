
// qqDlg.h : ͷ�ļ�
//

#pragma once
#include"packdef.h"

// CMyqqDlg �Ի���
class CMyqqDlg : public CDialogEx
{
// ����
public:
	CMyqqDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MYQQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	LRESULT RegisterMsg(WPARAM W,LPARAM L);
	LRESULT LoginMsg(WPARAM W,LPARAM L);
	DECLARE_MESSAGE_MAP()

public:
	LONGLONG m_edttel;
	CString m_edtname;
	CString m_edtpassword;
	LONGLONG m_edtqq;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
