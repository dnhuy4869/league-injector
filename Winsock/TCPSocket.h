#pragma once

#include <WinSock2.h>
#include <WS2tcpip.h>
#include <iphlpapi.h>

#pragma comment(lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#include <ThirdParty/json.hpp>

class TCPSocket final
{
	private:

	std::string m_IpAddress;

	DWORD m_Port;

	SOCKET m_Socket;

	bool m_bConnected = false;

	public:

	TCPSocket(std::string ipAdrr, DWORD port);

	~TCPSocket();

	bool Bind();

	bool Connect();

	bool Close();

	void SetTimeout(int miliseconds);

	bool Send(const char* buffer, int length, int flags = 0);

	bool Recv(char* buffer, int length, int flags = 0);

	bool Emit(const std::string& e, const nlohmann::json& payload = {});
};