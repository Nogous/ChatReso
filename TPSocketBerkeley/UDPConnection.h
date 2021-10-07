#pragma once
#include "Connection.h"

class UDPConnection : public Connection
{
public:
	UDPConnection();
	~UDPConnection();

	void SendMsg();
	void Receive();

private:

};