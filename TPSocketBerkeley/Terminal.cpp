#include "Terminal.h"

#include <iostream>
#include <Windows.h>
using namespace std;

Terminal::Terminal()
{
}

Terminal::~Terminal()
{
	closesocket(client);
}

SOCKET Terminal::Accept(SOCKET slisten)
{
	sockaddr_in clientInfo;
	int clientInfoLeng = sizeof(clientInfo);

	client = accept(slisten, (struct sockaddr*)&clientInfo, &clientInfoLeng);
	if (client == SOCKET_ERROR)
		cout << "error accept(): " << WSAGetLastError() << endl;

	//char* welcomMsg = "Connect to server\n";
	// send welcome msg
	//if (send(client, welcomMsg, strlen(welcomMsg), 0) == SOCKET_ERROR)
	//	cout << "error send(): " << WSAGetLastError() << endl;

	return client;
}