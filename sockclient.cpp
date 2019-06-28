#include "stdafx.h"
#include <WinSock2.h>
#include <iostream>
 
using namespace std;

#pragma comment(lib,"ws2_32.lib")

#define  IP   "127.0.0.1"
#define  IP_PORT	1234


int _tmain(int argc, _TCHAR* argv[])
{

	char szBuffer[MAXBYTE]={0};

	WSAData wsa;
	WSAStartup(MAKEWORD(2,2),&wsa);

	char str[100]={0};

	while(1)
	{
		SOCKET sock = socket(PF_INET,SOCK_STREAM,IPPROTO_TCP);
		sockaddr_in sockAddr;
		memset(&sockAddr,0,sizeof(sockaddr_in));
		sockAddr.sin_port=htons(IP_PORT);
		sockAddr.sin_addr.S_un.S_addr=inet_addr(IP);
		sockAddr.sin_family = PF_INET;

		int ret = connect(sock,(SOCKADDR*)&sockAddr,sizeof(SOCKADDR));
		if(ret == 0)
		{
			puts("connect success\n");
		}

		cout<< "input messages:\n"<<endl;
		cin>>str;

		ret = send(sock,str,strlen(str)+1,0);
		if(strcmp(str,"bye") == 0)
			break;

		ret = recv(sock,szBuffer,MAXBYTE,NULL);
		puts(szBuffer);

		memset(szBuffer,0,MAXBYTE);
		memset(str,0,strlen(str));

		//shutdown(sock,SD_SEND);

		closesocket(sock);
	}
	

	

	WSACleanup();

	system("pause");
	
	return 0;
}
