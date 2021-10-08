#include "UDPConnection.h"
using namespace uqac::network;

void UDPConnection::SendMsg(SOCKET outSock, std::string msg)
{
	// a changer
	if (send(outSock, msg.c_str(), strlen(msg.c_str()), 0) == SOCKET_ERROR)
		std::cout << "error send(): " << WSAGetLastError() << std::endl;
}

char* UDPConnection::Receive(SOCKET sConnect)
{
	char tmp[4096];

	return tmp;
}
