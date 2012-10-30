/**********************************************************************
 *
 * Solution   : Euro Truck Multiplayer
 * Project    : Euro Truck Multiplayer - Server
 * Licence    : GNU GPL v3
 * File       : CQuery.cpp
 * Description: None
 * Developers : 
 *              FRi <FRi.developing@gmail.com>
 *
 *********************************************************************/
#include "StdInc.h"
#ifdef _LINUX
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#define closesocket close
#else
typedef int socklen_t;
#endif

extern CServer * g_pServer;

CQuery::CQuery(unsigned int uiPort, CString strBindHost)
{
	m_uiPort = uiPort +1; //Query port
	m_strBindHost = strBindHost;

#ifdef _WIN32
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

	sockaddr_in addr;
	memset(&addr, 0, sizeof(sockaddr_in));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(m_uiPort);

	if(m_strBindHost.IsNotEmpty())
		addr.sin_addr.s_addr = inet_addr(m_strBindHost.Get());

	m_iSocket = socket(AF_INET, SOCK_DGRAM, 0);

#ifdef _WIN32
	unsigned long sockopt = 1;
	ioctlsocket (m_iSocket, FIONBIO, &sockopt);
#else
	fcntl(m_iSocket, F_SETFL, fcntl(m_iSocket, F_GETFL) | O_NONBLOCK); 
#endif

	if(bind(m_iSocket, (sockaddr *)&addr, sizeof(sockaddr_in)) == -1)
	{
		CLog::Printf("\nNie udalo sie zbindowac menadzera zapytan o porcie %d!\n", m_uiPort);
		SetState(false);
	} else {
		SetState(true);
	}
}

CQuery::~CQuery()
{
	if(m_iSocket != -1)
		closesocket(m_iSocket);

#ifdef WIN32
	WSACleanup();
#endif
}

void CQuery::Process()
{
	if(GetState())
	{
		static char szBuffer[1024];
		memset(szBuffer, 0, sizeof(szBuffer));

		sockaddr_in addr;
		memset(&addr, 0, sizeof(sockaddr_in));
		int iFromLen = sizeof(sockaddr_in);

		int iBytesRead = -1;

		while((iBytesRead = recvfrom(m_iSocket, szBuffer, sizeof(szBuffer), NULL, (sockaddr *)&addr, (socklen_t *)&iFromLen)) != -1)
		{
			// Pobieranie adresu ip z socketa.
			char szIpAddress[64];
			inet_ntop(addr.sin_family, &addr.sin_addr, szIpAddress, sizeof(szIpAddress));

			// Pobieranie portu z socketa.
			unsigned short usPort = ntohs(addr.sin_port);

			RakNet::BitStream bitStream((unsigned char*)szBuffer, iBytesRead, true);

			char szIdentifier[4];

			if(!bitStream.Read(szIdentifier, sizeof(szIdentifier)))
				continue;

			if(szIdentifier[0] != 'E' || szIdentifier[1] != 'T' || szIdentifier[2] != 'M' || szIdentifier[3] != 'P')
				continue;

			RakNet::BitStream bsReply;

			if(!bsReply.GetNumberOfBytesUsed())
			{
				char cType;

				if(!bitStream.Read(cType))
					continue;

				if(cType == 'h')
				{
					bsReply.Write(szIdentifier, sizeof(szIdentifier));
					bsReply.Write(cType);

					size_t len = g_pServer->GetVarValue("hostname").GetLength();
					bsReply.Write((int)len);
					bsReply.Write(g_pServer->GetVarValue("hostname").Get(), len);
				} else if(cType == 'p') {
					bsReply.Write(szIdentifier, sizeof(szIdentifier));
					bsReply.Write(cType);

					int iMaxPlayers = atoi(g_pServer->GetVarValue("maxplayers").Get());
					bsReply.Write((int)iMaxPlayers);
				}
			}
			
			if(bsReply.GetNumberOfBytesUsed() > 0)
			{
				if(sendto(m_iSocket, (const char *)bsReply.GetData(), bsReply.GetNumberOfBytesUsed(), NULL, 
					(sockaddr *)&addr, sizeof(sockaddr_in)) != bsReply.GetNumberOfBytesUsed())
				{
					//Error
				}
			}
		}
	}
}

const char * CQuery::inet_ntop(int af, const void * src, char * dst, int cnt)
{
	if(af == AF_INET || af == PF_INET)
	{
		sockaddr_in in;
		memset(&in, 0, sizeof(in));
		in.sin_family = af;
		memcpy(&in.sin_addr, src, sizeof(in_addr));
		getnameinfo((sockaddr *)&in, sizeof(sockaddr_in), dst, cnt, NULL, 0, NI_NUMERICHOST);
		return dst;
	}
	else if(af == AF_INET6 || af == PF_INET6)
	{
		struct sockaddr_in6 in;
		memset(&in, 0, sizeof(in));
		in.sin6_family = af;
		memcpy(&in.sin6_addr, src, sizeof(in.sin6_addr));
		getnameinfo((sockaddr *)&in, sizeof(sockaddr_in6), dst, cnt, NULL, 0, NI_NUMERICHOST);
		return dst;
	}
	return NULL;
}