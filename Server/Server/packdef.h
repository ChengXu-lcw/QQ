#pragma once


#define _DEF_PROTOCOL_BASE    10
//注册
#define _DEF_PROTOCOL_REGISTER_RQ   _DEF_PROTOCOL_BASE +1
#define _DEF_PROTOCOL_REGISTER_RS   _DEF_PROTOCOL_BASE +2
//登录
#define _DEF_PROTOCOL_LOGIN_RQ   _DEF_PROTOCOL_BASE +3
#define _DEF_PROTOCOL_LOGIN_RS   _DEF_PROTOCOL_BASE +4
//获取好友列表
#define _DEF_PROTOCOL_GETFRIENDLIST_RQ   _DEF_PROTOCOL_BASE +5
#define _DEF_PROTOCOL_GETFRIENDLIST_RS   _DEF_PROTOCOL_BASE +6
//聊天
#define _DEF_PROTOCOL_SELECTFRIENDCHAT_RQ   _DEF_PROTOCOL_BASE +7
#define _DEF_PROTOCOL_SELECTFRIENDCHAT_RS   _DEF_PROTOCOL_BASE +8
//"心跳"协议
#define _DEF_KEEPALIVE_RS   _DEF_PROTOCOL_BASE +9
//消息
#define UM_REGISTERMSG  WM_USER +1
#define UM_LOGINMSG  WM_USER +2
#define UM_GETFRIENDLISTMSG  WM_USER +3
#define UM_CHATMSG  WM_USER +4
//协议包
//注册
#define MAXSIZE   45
#define MAXNUM    30
#define DEFCONTENTNUM  1024
#define DEFSQLLEN  300

#define _login_success 0
#define _login_error 1
#define _login_nouser 2

#define SERVERIP "127.0.0.1"
struct STRU_REGISTER_RQ//注册申请
{
    char m_nType; //协议类型
	long long m_tel;
	char  m_szName[MAXSIZE];
	char  m_szPassword[MAXSIZE];
};
struct STRU_REGISTER_RS//注册(回复)结果
{
    char m_nType; //协议类型
	long long m_qq;
	//char  m_szResult;
};
//登录

struct STRU_LOGIN_RQ//登录申请
{
	char m_nType; //协议类型
	long long m_qq;
	char  m_szPassword[MAXSIZE];
};

struct STRU_LOGIN_RS//登录结果
{
	char m_nType; //协议类型
	char  m_szResult;
};

struct STRU_GETFRIENDLIST_RQ//获取好友列表
{
	char m_nType; //协议类型
	long long m_qq;	
};

struct FriendInfo//好友信息
{
	char m_szName[MAXSIZE];
	long long m_qq;
	char   m_szState;//好友在线状态
};

struct STRU_GETFRIENDLIST_RS//获取好友列表结果
{
	char m_nType; //协议类型
	FriendInfo m_aryInfo[MAXNUM];//一次发送好友列表的好友个数
	int     m_nNum;
};

struct STRU_SELECTFRIENDCHAT_RQ//选择好友聊天
{
	char m_nType; //协议类型
	long long m_qq;	
	long long m_friendqq;
	char  m_szContent[DEFCONTENTNUM];//聊天内容
};
/*
    用户信息表 user(u_qq,u_tel,u_name,u_password)
	用户好友表user_friend(u_qq,u_friendqq)
	用户状态   user_state(u_qq,u_state,u_time)
*/
