#include "UDPConnection.h"

void UDPConnection::SendMsg(SOCKET outSock, std::string msg)
{
	// a changer
	if (send(outSock, msg.c_str(), strlen(msg.c_str()), 0) == SOCKET_ERROR)
		cout << "error send(): " << WSAGetLastError() << endl;
}

std::string UDPConnection::Receive(SOCKET sConnect)
{
	return std::string();
}
