#pragma once
#include "Connection.h"

class TCPConnection : public Connection
{
public:

	void SendMsg(SOCKET outSock, std::string msg) override;
	std::string Receive(SOCKET sConnect) override;

private:

};