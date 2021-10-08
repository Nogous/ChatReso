#include "TCPConnection.h"

using namespace uqac::network;

void TCPConnection::SendMsg(SOCKET outSock, std::string msg)
{
	if (send(outSock, msg.c_str(), strlen(msg.c_str()), 0) == SOCKET_ERROR)
		std::cout << "error send(): " << WSAGetLastError() << std::endl;
}

char* TCPConnection::Receive(SOCKET sConnect)
{
	char recvbuf[4096];

	memset(&recvbuf, 0, sizeof(recvbuf));

	if (recv(sConnect, recvbuf, 256, 0) == SOCKET_ERROR)
		std::cout << "error recv(): " << WSAGetLastError() << std::endl;

	return recvbuf;
}
