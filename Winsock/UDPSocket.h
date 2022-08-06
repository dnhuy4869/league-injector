#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <ThirdParty/json.hpp>

class UDPSocket
{
	private:

	std::string m_IpAddress;

	DWORD m_Port;

	SOCKET m_Socket;

	SOCKADDR_IN m_Sockaddr;

	bool m_bConnected = false;

	public:

	UDPSocket(std::string ipAdrr, DWORD port);

	~UDPSocket();

	bool Bind();

	bool Connect();

	bool Close();

	bool Send(const char* buffer, int length, int flags = 0);

	bool Recv(char* buffer, int length, int flags = 0);
};