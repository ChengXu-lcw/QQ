#pragma once


#define _DEF_PROTOCOL_BASE    10
//ע��
#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2
//��¼
#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4
//��ȡ�����б�
#define _DEF_PROTOCOL_GETFRIENDLIST_RQ   _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_GETFRIENDLIST_RS   _DEF_PROTOCOL_BASE +6
//����
#define _DEF_PROTOCOL_SELECTFRIENDCHAT_RQ   _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_SELECTFRIENDCHAT_RS   _DEF_PROTOCOL_BASE +8
//"����"Э��
#define _DEF_KEEPALIVE_RS   _DEF_PROTOCOL_BASE +9
//��Ϣ
#define UM_REGISTERMSG  WM_USER +1
#define UM_LOGINMSG  WM_USER +2
#define UM_GETFRIENDLISTMSG  WM_USER +3
#define UM_CHATMSG  WM_USER +4
//Э���
//ע��
#define MAXSIZE   45
#define MAXNUM    30
#define DEFCONTENTNUM  1024
#define DEFSQLLEN  300

#define _login_success 0
#define _login_error 1
#define _login_nouser 2

#define SERVERIP "127.0.0.1"
struct STRU_REGISTER_RQ//ע������
{
    char m_nType; //Э������
	long long m_tel;
	char  m_szName[MAXSIZE];
	char  m_szPassword[MAXSIZE];
};
struct STRU_REGISTER_RS//ע��(�ظ�)���
{
    char m_nType; //Э������
	long long m_qq;
	//char  m_szResult;
};
//��¼

struct STRU_LOGIN_RQ//��¼����
{
	char m_nType; //Э������
	long long m_qq;
	char  m_szPassword[MAXSIZE];
};

struct STRU_LOGIN_RS//��¼���
{
	char m_nType; //Э������
	char  m_szResult;
};

struct STRU_GETFRIENDLIST_RQ//��ȡ�����б�
{
	char m_nType; //Э������
	long long m_qq;	
};

struct FriendInfo//������Ϣ
{
	char m_szName[MAXSIZE];
	long long m_qq;
	char   m_szState;//��������״̬
};

struct STRU_GETFRIENDLIST_RS//��ȡ�����б���
{
	char m_nType; //Э������
	FriendInfo m_aryInfo[MAXNUM];//һ�η��ͺ����б�ĺ��Ѹ���
	int     m_nNum;
};

struct STRU_SELECTFRIENDCHAT_RQ//ѡ���������
{
	char m_nType; //Э������
	long long m_qq;	
	long long m_friendqq;
	char  m_szContent[DEFCONTENTNUM];//��������
};
/*
    �û���Ϣ�� user(u_qq,u_tel,u_name,u_password)
	�û����ѱ�user_friend(u_qq,u_friendqq)
	�û�״̬   user_state(u_qq,u_state,u_time)
*/
