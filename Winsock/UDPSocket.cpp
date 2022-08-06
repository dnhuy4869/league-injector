#include "UDPSocket.h"

UDPSocket::UDPSocket(std::string ipAdrr, DWORD port)
{
	this->m_IpAddress = ipAdrr;
	this->m_Port = port;
}

UDPSocket::~UDPSocket()
{
	closesocket(m_Socket);
}

bool UDPSocket::Bind()
{
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN Hints;
	Hints.sin_family = AF_INET;
	Hints.sin_port = htons(m_Port);
	inet_pton(AF_INET, m_IpAddress.c_str(), &Hints.sin_addr.s_addr);

	int error = bind(m_Socket, (SOCKADDR*)&Hints, sizeof(Hints));
	if (error == SOCKET_ERROR)
	{
		return false;
	}

	m_bConnected = true;
	return true;
}

bool UDPSocket::Connect()
{
	m_Socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	m_Sockaddr.sin_family = AF_INET;
	m_Sockaddr.sin_port = htons(m_Port);
	inet_pton(AF_INET, m_IpAddress.c_str(), &m_Sockaddr.sin_addr.s_addr);

	m_bConnected = true;
	return true;
}

bool UDPSocket::Close()
{
	if (m_bConnected)
	{
		closesocket(m_Socket);

		m_bConnected = false;
		return true;
	}

	return false;
}

bool UDPSocket::Send(const char* buffer, int length, int flags)
{
	if (sendto(m_Socket, buffer, length, flags, (sockaddr*)&m_Sockaddr, sizeof(m_Sockaddr)) <= 0)
	{
		return false;
	}

	return true;
}

bool UDPSocket::Recv(char* buffer, int length, int flags)
{
	ZeroMemory(buffer, length);

	int size = sizeof(m_Sockaddr);
	if (recvfrom(m_Socket, buffer, length, flags, (sockaddr*)&m_Sockaddr, &size) <= 0)
	{
		return false;
	}

	return true;
}