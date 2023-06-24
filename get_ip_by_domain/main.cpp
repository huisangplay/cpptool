#pragma comment(lib,"WS2_32.Lib")
#include<cstdio>
#include<string>
#include "WinSock.h"
#include "inaddr.h"
using namespace std;

BOOL  GetRealIpByDomainName(char* szHost, char szIp[50][100], int* nCount)
{
	WSADATA wsaData;
	HOSTENT* pHostEnt;
	int nAdapter = 0;
	struct sockaddr_in   sAddr;
	if (WSAStartup(0x0101, &wsaData))
	{
		printf(" gethostbyname error for host:\n");
		return FALSE;
	}
	pHostEnt = gethostbyname(szHost);
	if (pHostEnt)
	{
		while (pHostEnt->h_addr_list[nAdapter])
		{
			memcpy(&sAddr.sin_addr.s_addr, pHostEnt->h_addr_list[nAdapter], pHostEnt->h_length);

			sprintf_s(szIp[nAdapter], "%s", inet_ntoa(sAddr.sin_addr));

			nAdapter++;
		}

		*nCount = nAdapter;
	}
	else
	{
		DWORD  dwError = GetLastError();
		*nCount = 0;
	}
	WSACleanup();
	return TRUE;
}

int main(int argc, char* argv[])
{
	int nIpCount = 0;
	char szIpList[50][100];
	char szDomain[256] = { 0 };
	char szIp[1024] = { 0 };
	strcpy_s(szDomain, "www.baidu.com");
	GetRealIpByDomainName(szDomain, szIpList, &nIpCount);

	for (int i = 0; i < nIpCount; i++)
	{
		strcat_s(szIp, szIpList[i]);
		strcat_s(szIp, "\t");
	}
	printf("DomainName : %s \n", szDomain);
	printf("Real IPList : %s", szIp);
	return 0;
}