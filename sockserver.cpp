// sockserver.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <WinSock2.h>


#pragma comment(lib,"ws2_32.lib")

#define IP				"127.0.0.1"
#define IP_PORT			1234
#define LISTEN_COUNT	20

int _tmain(int argc, _TCHAR* argv[])
{
	
	char buf[100]={0};
	int nRet = 0;

	//��ʼ��
	WSAData wsdata;
	nRet = WSAStartup(MAKEWORD(2,2),&wsdata);
	if (nRet != 0)
	{
		puts("WSAStartip failed\n");
		return 0;
	}

	//�����׽���
	SOCKET sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	//��
	sockaddr_in sockaddr;
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(IP);
	sockaddr.sin_port = htons(IP_PORT);
	bind(sock,(SOCKADDR*)&sockaddr,sizeof(SOCKADDR));

	//����
	nRet  = listen(sock,LISTEN_COUNT);
	if(nRet < 0)
	{
		puts("listen failed\n");
	}
	else
		puts("listening....\n");

	//���տͻ���
	SOCKADDR clientsockAddr;
	int nSize = sizeof(SOCKADDR);
	

	while(1)
	{
		SOCKET sockClient = accept(sock,(SOCKADDR*)&clientsockAddr,&nSize);
		if(sockClient!= NULL)
		{
			printf("client connected!\n");
		}
		//��������
		nRet = recv(sockClient,buf,sizeof(buf),0);
		puts(buf);
		

		//��������
		char *str = "hello client!";
		nRet = send(sockClient,str,strlen(str)+1,NULL);

		if(strcmp(buf,"bye") ==0)
			break;
		memset(buf,0,100);

		closesocket(sockClient);
	}
	

	closesocket(sock);
	//closesocket(sockClient);

	WSACleanup();

	return 0;
}

