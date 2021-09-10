
// qqDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "qq.h"
#include "qqDlg.h"
#include "afxdialogex.h"


#include"DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyqqDlg 对话框



CMyqqDlg::CMyqqDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyqqDlg::IDD, pParent)
	, m_edttel(0)
	, m_edtname(_T(""))
	, m_edtpassword(_T(""))
	, m_edtqq(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMyqqDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDT_TEP, m_edttel);
	DDX_Text(pDX, IDC_EDT_NAME, m_edtname);
	DDX_Text(pDX, IDC_EDT_PWD, m_edtpassword);
	DDX_Text(pDX, IDC_EDT_QQ, m_edtqq);
}

BEGIN_MESSAGE_MAP(CMyqqDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyqqDlg::OnBnClickedButton1)
	ON_MESSAGE(UM_REGISTERMSG,&CMyqqDlg::RegisterMsg)
	ON_MESSAGE(UM_LOGINMSG,&CMyqqDlg::LoginMsg)

	ON_BN_CLICKED(IDC_BUTTON2, &CMyqqDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMyqqDlg 消息处理程序
//注册
LRESULT CMyqqDlg::RegisterMsg(WPARAM W,LPARAM L)
{
	long long qq=*(long long*)W;
	m_edtqq=qq;
	UpdateData(FALSE);//将数据更新到窗口上
	return 0;

}
//登录
LRESULT CMyqqDlg::LoginMsg(WPARAM W,LPARAM L)
{
	UpdateData(TRUE);
	//1.定义一个新窗口
	CDlgMain dlg;
	//2.切换主窗口
	theApp.m_pMainWnd=&dlg;
	//3.记录QQ号
	dlg.m_qq=m_edtqq;
	//4.销毁登录窗口
	EndDialog(IDOK);
	//5.弹出新窗口
	dlg.DoModal();
	
	
	return 0;
}
BOOL CMyqqDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMyqqDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMyqqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMyqqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyqqDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	STRU_REGISTER_RQ srr;
	srr.m_nType=_DEF_PROTOCOL_REGISTER_RQ;
	strcpy_s(srr.m_szName,sizeof(srr.m_szName),m_edtname);
	strcpy_s(srr.m_szPassword,sizeof(srr.m_szPassword),m_edtpassword);
	srr.m_tel=m_edttel;

	theApp.m_kernel.SendData((char*)&srr,sizeof(srr));
}


void CMyqqDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	STRU_LOGIN_RQ slr;
	slr.m_nType=_DEF_PROTOCOL_LOGIN_RQ;
	slr.m_qq=m_edtqq;
	strcpy_s(slr.m_szPassword,sizeof(slr.m_szPassword),m_edtpassword);
	theApp.m_kernel.SendData((char*)&slr,sizeof(slr));
}
