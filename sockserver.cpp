// sockserver.cpp : 定义控制台应用程序的入口点。
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

	//初始化
	WSAData wsdata;
	nRet = WSAStartup(MAKEWORD(2,2),&wsdata);
	if (nRet != 0)
	{
		puts("WSAStartip failed\n");
		return 0;
	}

	//创建套接字
	SOCKET sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);

	//绑定
	sockaddr_in sockaddr;
	memset(&sockaddr,0,sizeof(sockaddr));
	sockaddr.sin_family = PF_INET;
	sockaddr.sin_addr.s_addr = inet_addr(IP);
	sockaddr.sin_port = htons(IP_PORT);
	bind(sock,(SOCKADDR*)&sockaddr,sizeof(SOCKADDR));

	//监听
	nRet  = listen(sock,LISTEN_COUNT);
	if(nRet < 0)
	{
		puts("listen failed\n");
	}
	else
		puts("listening....\n");

	//接收客户端
	SOCKADDR clientsockAddr;
	int nSize = sizeof(SOCKADDR);
	

	while(1)
	{
		SOCKET sockClient = accept(sock,(SOCKADDR*)&clientsockAddr,&nSize);
		if(sockClient!= NULL)
		{
			printf("client connected!\n");
		}
		//接收数据
		nRet = recv(sockClient,buf,sizeof(buf),0);
		puts(buf);
		

		//返回数据
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

