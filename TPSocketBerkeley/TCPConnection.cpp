#include "TCPConnection.h"

void TCPConnection::SendMsg(SOCKET outSock, std::string msg)
{
	if (send(outSock, msg.c_str(), strlen(msg.c_str()), 0) == SOCKET_ERROR)
		cout << "error send(): " << WSAGetLastError() << endl;
}

char* TCPConnection::Receive(SOCKET sConnect)
{
	char* recvbuf;

	memset(&recvbuf, 0, sizeof(recvbuf));

	if (recv(sConnect, recvbuf, 256, 0) == SOCKET_ERROR)
		cout << "error recv(): " << WSAGetLastError() << endl;

	return recvbuf;
}
