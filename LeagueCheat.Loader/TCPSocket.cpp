#include "./TCPSocket.h"

TCPSocket::TCPSocket(PCSTR ipAdrr, DWORD port)
{
	this->m_IpAddress = ipAdrr;
	this->m_Port = port;
}

TCPSocket::~TCPSocket()
{
	if (this->m_bConnected)
	{
		closesocket(this->m_Socket);
		this->m_bConnected = false;
	}
}

bool TCPSocket::Connect()
{
	this->m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (this->m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN hints;
	hints.sin_family = AF_INET;
	hints.sin_port = htons(this->m_Port);
	inet_pton(AF_INET, this->m_IpAddress, &hints.sin_addr.s_addr);

	if (connect(this->m_Socket, (SOCKADDR*)&hints, sizeof(hints)) == SOCKET_ERROR)
	{
		return false;
	}

	this->m_bConnected = true;
	return true;
}

bool TCPSocket::Close()
{
	if (this->m_bConnected)
	{
		closesocket(this->m_Socket);

		this->m_bConnected = false;
		return true;
	}

	return false;
}

void TCPSocket::SetTimeout(int miliseconds)
{
	int timeout = miliseconds;
	int timeoutSize = sizeof(timeout);
	setsockopt(this->m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, timeoutSize);
	setsockopt(this->m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, timeoutSize);
}

bool TCPSocket::Send(const char* buffer, int length, int flags)
{
	if (send(this->m_Socket, buffer, length, flags) <= 0)
	{
		return false;
	}

	return true;
}

bool TCPSocket::Recv(char* buffer, int length, int flags)
{
	ZeroMemory(buffer, length);

	if (recv(this->m_Socket, buffer, length, flags) <= 0)
	{
		return false;
	}

	return true;
}

bool TCPSocket::Emit(std::string e, nlohmann::json payload)
{
	nlohmann::json data = payload;
	data["event"] = e;

	const std::string data_string = data.dump();

	return this->Send(data_string.c_str(), data_string.length());
}
