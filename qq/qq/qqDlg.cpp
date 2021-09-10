
// qqDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "qq.h"
#include "qqDlg.h"
#include "afxdialogex.h"


#include"DlgMain.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CMyqqDlg �Ի���



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


// CMyqqDlg ��Ϣ�������
//ע��
LRESULT CMyqqDlg::RegisterMsg(WPARAM W,LPARAM L)
{
	long long qq=*(long long*)W;
	m_edtqq=qq;
	UpdateData(FALSE);//�����ݸ��µ�������
	return 0;

}
//��¼
LRESULT CMyqqDlg::LoginMsg(WPARAM W,LPARAM L)
{
	UpdateData(TRUE);
	//1.����һ���´���
	CDlgMain dlg;
	//2.�л�������
	theApp.m_pMainWnd=&dlg;
	//3.��¼QQ��
	dlg.m_qq=m_edtqq;
	//4.���ٵ�¼����
	EndDialog(IDOK);
	//5.�����´���
	dlg.DoModal();
	
	
	return 0;
}
BOOL CMyqqDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMyqqDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyqqDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMyqqDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	STRU_LOGIN_RQ slr;
	slr.m_nType=_DEF_PROTOCOL_LOGIN_RQ;
	slr.m_qq=m_edtqq;
	strcpy_s(slr.m_szPassword,sizeof(slr.m_szPassword),m_edtpassword);
	theApp.m_kernel.SendData((char*)&slr,sizeof(slr));
}
