#include "./TCPSocket.h"

TCPSocket::TCPSocket(std::string ipAdrr, DWORD port)
{
	this->m_IpAddress = ipAdrr;
	this->m_Port = port;
}

TCPSocket::~TCPSocket()
{
	closesocket(m_Socket);
}

bool TCPSocket::Bind()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
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

	error = listen(m_Socket, SOMAXCONN);
	if (error == SOCKET_ERROR)
	{
		return false;
	}

	m_bConnected = true;
	return true;
}

bool TCPSocket::Connect()
{
	m_Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_Socket == INVALID_SOCKET)
	{
		return false;
	}

	SOCKADDR_IN hints;
	hints.sin_family = AF_INET;
	hints.sin_port = htons(this->m_Port);
	inet_pton(AF_INET, m_IpAddress.c_str(), &hints.sin_addr.s_addr);

	if (connect(m_Socket, (SOCKADDR*)&hints, sizeof(hints)) == SOCKET_ERROR)
	{
		return false;
	}

	m_bConnected = true;
	return true;
}

bool TCPSocket::Close()
{
	if (m_bConnected)
	{
		closesocket(m_Socket);

		m_bConnected = false;
		return true;
	}

	return false;
}

void TCPSocket::SetTimeout(int miliseconds)
{
	int timeout = miliseconds;
	int timeoutSize = sizeof(timeout);
	setsockopt(m_Socket, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, timeoutSize);
	setsockopt(m_Socket, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, timeoutSize);
}

bool TCPSocket::Send(const char* buffer, int length, int flags)
{
	if (send(m_Socket, buffer, length, flags) <= 0)
	{
		return false;
	}

	return true;
}

bool TCPSocket::Recv(char* buffer, int length, int flags)
{
	ZeroMemory(buffer, length);

	if (recv(m_Socket, buffer, length, flags) <= 0)
	{
		return false;
	}

	return true;
}

bool TCPSocket::Emit(const std::string& e, const nlohmann::json& payload)
{
	nlohmann::json data = payload;
	data["event"] = e;

	const std::string& data_string = data.dump();

	return this->Send(data_string.c_str(), data_string.length());
}