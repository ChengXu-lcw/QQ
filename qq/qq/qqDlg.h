
// qqDlg.h : 头文件
//

#pragma once
#include"packdef.h"

// CMyqqDlg 对话框
class CMyqqDlg : public CDialogEx
{
// 构造
public:
	CMyqqDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MYQQ_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
