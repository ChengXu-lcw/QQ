#include<iostream>
using namespace std;
#include"TCPKernel.h"
int main()
{
	IKernel *p=new TCPKernel;
	if(p->Open())
		cout<<"��������ʼ���ɹ���"<<endl;
	//ע�����
		/*STRU_REGISTER_RQ srr;
		srr.m_nType=_DEF_PROTOCOL_REGISTER_RQ;
		strcpy_s(srr.m_szName,MAXSIZE,"textone");
		strcpy_s(srr.m_szPassword,MAXSIZE,"123456");
		srr.m_tel=18945723419;
		p->DealData((char*)&srr,0);*/
	//��¼����
	/*  STRU_LOGIN_RQ srr;
		srr.m_nType=_DEF_PROTOCOL_LOGIN_RQ;
		srr.m_qq=7;
		strcpy_s(srr.m_szPassword,MAXSIZE,"123456");	
		p->DealData((char*)&srr,0);*/
	//��ȡ���Ѳ���
	/*STRU_GETFRIENDLIST_RQ srr;
		srr.m_nType=_DEF_PROTOCOL_GETFRIENDLIST_RQ;
		srr.m_qq=7;	
		p->DealData((char*)&srr,0); */
	system("pause");
	return 0;
}