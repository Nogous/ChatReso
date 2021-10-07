#pragma once
#include "Connection.h"

class TCPConnection : public Connection
{
public:
	TCPConnection();
	~TCPConnection();

	void SendMsg();
	void Receive();

private:

};