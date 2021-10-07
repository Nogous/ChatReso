#pragma once
#include <WinSock2.h>

class Terminal
{
public:
	Terminal();
	~Terminal();

	SOCKET Accept(SOCKET slisten);

private:
	SOCKET client;
};