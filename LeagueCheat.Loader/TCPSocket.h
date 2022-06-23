#pragma once

#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include "./ThirdParty/json.hpp"

class TCPSocket final
{
	private:

	PCSTR m_IpAddress;
	DWORD m_Port;

	SOCKET m_Socket;
	bool m_bConnected = false;

	public:

	TCPSocket(PCSTR ipAdrr, DWORD port);
	~TCPSocket();

	bool Connect();

	bool Close();

	void SetTimeout(int miliseconds);

	bool Send(const char* buffer, int length, int flags = 0);

	bool Recv(char* buffer, int length, int flags = 0);

	bool Emit(std::string e, nlohmann::json payload = {});
};