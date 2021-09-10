#include"TCPKernel.h"
#include"TCPNet.h"

	TCPKernel::TCPKernel()
	{
		m_pNet=new TCPNet(this);
	}
	TCPKernel::~TCPKernel()
	{
		delete m_pNet;
		m_pNet=NULL;
	}

	 DWORD WINAPI TCPKernel::ThreadProc(LPVOID lpParameter)
	{
		TCPKernel *pthis=(TCPKernel *)lpParameter;
		HANDLE hTimer = CreateWaitableTimer(0,0,0);
		LARGE_INTEGER li;
		SetWaitableTimer(hTimer,&li,5000,0,0,0);
		while(1)
		{
			WaitForSingleObject(hTimer,INFINITE);
			//遍历MAP
			auto ite=pthis->m_mapSocketToTime.begin();
			while(ite!=pthis->m_mapSocketToTime.end())
			{
				DWORD dwTime = (GetTickCount() -ite->second)/1000;
				ite++;

			}
		}
		return 0;
	}

   bool TCPKernel::Open() 
   {
	   if(!m_sql.ConnectMySql("localhost","root","l81835","0302qq"))
		   return false;
	   if(!m_pNet->InitNetWork())
	   {
		   return false;
	   }

	   a=CreateThread(0,0,&ThreadProc,this,0,0);
	   return true;
   }
   void TCPKernel::Close() 
   {
	   m_sql.DisConnect();
	   m_pNet->UnInitNetWork();
	   //销毁线程
	   if(WAIT_TIMEOUT == WaitForSingleObject(a,100))
			TerminateThread(a,-1);

		CloseHandle(a);
		a = NULL;
   }
   void TCPKernel::RegisterRq(char *szbuf,SOCKET sockWaiter)
   {
	   STRU_REGISTER_RQ* psrr=(STRU_REGISTER_RQ*)szbuf;
	   STRU_REGISTER_RS srr;
	   srr.m_nType=_DEF_PROTOCOL_REGISTER_RS;
	   srr.m_qq=0;
	   //1.直接将用户信息写入数据库
	   char szsql[DEFSQLLEN]={0};
	   list<string> lststr;
	   sprintf_s(szsql, "insert into user(u_tel,u_name,u_password) values(%lld,'%s','%s')",psrr->m_tel,psrr->m_szName,psrr->m_szPassword);
	   if(m_sql.UpdateMySql(szsql))
	   {
		   //获取QQ
		   sprintf_s(szsql,"select u_qq from user where u_tel= %lld",psrr->m_tel);
		   m_sql.SelectMySql(szsql,1,lststr);
        
		   if(lststr.size()>0)
		   {
			   string strQQ=lststr.front();
			   lststr.pop_front();
			   long long qq=_atoi64(strQQ.c_str());
			   srr.m_qq=qq;
            //2.写入用户状态
			   sprintf_s(szsql,"insert into user_state(u_qq) value(%lld)",qq);
			   m_sql.UpdateMySql(szsql);
		   }
	   }
	   

	   //3.发送回复
	   m_pNet->SendData(sockWaiter,(char*)&srr,sizeof(srr));
   }

   void TCPKernel::LoginRq(char *szbuf,SOCKET sockWaiter)
   {
	   STRU_LOGIN_RQ* pslr=(STRU_LOGIN_RQ*)szbuf;
	   char szsql[DEFSQLLEN]={0};
	   STRU_LOGIN_RS slr;
	   slr.m_nType=_DEF_PROTOCOL_LOGIN_RS;
	   slr.m_szResult=_login_nouser;
	   list<string> lststr;
	   sprintf_s(szsql,"select  u_password from user where u_qq=%lld",pslr->m_qq);
	   m_sql.SelectMySql(szsql,1,lststr);
	   //校验用户名称和密码
	   if(lststr.size()>0)
	   {
		   slr.m_szResult=_login_error;
		   string strPassword=lststr.front();
			   lststr.pop_front();
			   if(0==strcmp(pslr->m_szPassword,strPassword.c_str()))
			   {
				   //登陆成功
				   slr.m_szResult=_login_success;
				   m_mapQQToSocket[pslr->m_qq]=sockWaiter;
		   //更改在线状态
				   sprintf_s(szsql,"update user_state set u_state=1,u_time=now() where u_qq=%lld",pslr->m_qq);
				   m_sql.UpdateMySql(szsql);
			   }
	   }
	   //发送回复
	   m_pNet->SendData(sockWaiter,(char*)&slr,sizeof(slr));
   }

   void TCPKernel::GetFriendListRq(char *szbuf,SOCKET sockWaiter)
   {
	   STRU_GETFRIENDLIST_RQ* psgr=(STRU_GETFRIENDLIST_RQ*)szbuf;
	   char szsql[DEFSQLLEN]={0};
	   list<string> lststr;
	   STRU_GETFRIENDLIST_RS sgr;
	   sgr.m_nType=_DEF_PROTOCOL_GETFRIENDLIST_RS;
	   //找到所有好友
	   sprintf_s(szsql,"SELECT * FROM 0302qq.a where u_qq=%lld;",psgr->m_qq);   
	   m_sql.SelectMySql(szsql,3,lststr);
	   int i=0;
	    while(lststr.size()>0)
	   {
		  string strFriendQQ=lststr.front();
			   lststr.pop_front();
		  string strFriendName=lststr.front();
			   lststr.pop_front();
		  string strFriendState=lststr.front();
			   lststr.pop_front();
			   
	 strcpy_s(sgr.m_aryInfo[i].m_szName,MAXSIZE,strFriendName.c_str());
	 sgr.m_aryInfo[i].m_qq=_atoi64(strFriendQQ.c_str());
	 sgr.m_aryInfo[i].m_szState=*strFriendState.c_str();
		i++;
		if(i==MAXNUM||lststr.size()==0)
		{
			//发送回复
			sgr.m_nNum=i;
			m_pNet->SendData(sockWaiter,(char*)&sgr,sizeof(sgr));
		    i=0;
		}
			
		}
	   
   }

 void TCPKernel::SelectFriendChatRq(char *szbuf,SOCKET sockWaiter)
 {
	   STRU_SELECTFRIENDCHAT_RQ *pssr=(STRU_SELECTFRIENDCHAT_RQ *)szbuf;
	   SOCKET sockFriend = m_mapQQToSocket[pssr->m_friendqq];
	   if(sockFriend)
	   {
		   m_pNet->SendData(sockFriend,szbuf,sizeof(STRU_SELECTFRIENDCHAT_RQ));

	   }
	   else //发送离线消息
	   {
	   }

 }

 ProtocolMap m_protocolMapEntries[]=
 {
	 {_DEF_PROTOCOL_REGISTER_RQ,&TCPKernel::RegisterRq},
	 {_DEF_PROTOCOL_LOGIN_RQ,&TCPKernel::LoginRq},
	 {_DEF_PROTOCOL_GETFRIENDLIST_RQ,&TCPKernel::GetFriendListRq},
	 {_DEF_PROTOCOL_SELECTFRIENDCHAT_RQ,&TCPKernel::SelectFriendChatRq},
	 {_DEF_KEEPALIVE_RS,&TCPKernel::KeepAlive},
	 {0,0},
 };
 
 void TCPKernel::KeepAlive(char *szbuf,SOCKET sockWaiter)
 {
	 m_mapSocketToTime[sockWaiter] = GetTickCount();


 }

   void TCPKernel::DealData(char *szbuf,SOCKET sockWaiter) 
   {
	   //数据处理
	  /* switch (*szbuf)
	   {
	   case _DEF_PROTOCOL_REGISTER_RQ:
		   {
		   RegisterRq(szbuf,sockWaiter);
		   }
		   break;
	   case _DEF_PROTOCOL_LOGIN_RQ:
		   {
            LoginRq(szbuf,sockWaiter);
		   }
		   break;
	   case _DEF_PROTOCOL_GETFRIENDLIST_RQ:
		   {
            GetFriendListRq(szbuf,sockWaiter);
		   }
		   break;
	   case _DEF_PROTOCOL_SELECTFRIENDCHAT_RQ:
		   {
            SelectFriendChatRq(szbuf,sockWaiter);
		   }
		   break;
	   default:
		   break;
	   }*/
	   //遍历结构体数组
	   int i=0;
	   while(1)
	   {
		   if(m_protocolMapEntries[i].m_ntype==*szbuf)
		   {
			   //调用函数指针
				   (this->*m_protocolMapEntries[i].m_pfun)(szbuf,sockWaiter);
				   break;
		   }
		   else if(m_protocolMapEntries[i].m_ntype==0&&m_protocolMapEntries[i].m_pfun==0)
			   break;
		   i++;
	   }


   }

