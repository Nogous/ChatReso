// TPSocketBerkeley.cpp : définit le point d'entrée de l'application.
//

#pragma comment(lib, "ws2_32.lib")

#include "TPSocketBerkeley.h"
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
using namespace std;

#define PORT 80

void serveur()
{
	char recvbuf[256];

	// Init WISOCK
	WSADATA wsData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsData) != 0)
		ExitProcess(EXIT_FAILURE);

	//creation des socket
	SOCKET slisten, client;

	//parametarge socket
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if (slisten == INVALID_SOCKET)
		cout << "error socket(): " << WSAGetLastError() << endl;

	sockaddr_in info;
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family = AF_INET;
	info.sin_port = htons(PORT);
	int infoLeng = sizeof(info);

	if (bind(slisten, (struct sockaddr*)&info, infoLeng) == SOCKET_ERROR)
		cout << "error bind(): " << WSAGetLastError() << endl;

	if (listen(slisten, SOMAXCONN) == SOCKET_ERROR)
		cout << "error listen(): " << WSAGetLastError() << endl;

	sockaddr_in clientInfo;
	int clientInfoLeng = sizeof(clientInfo);

	char* msg = "Connect to server";


	client = accept(slisten, (struct sockaddr*)&clientInfo, &clientInfoLeng);
	if (client == SOCKET_ERROR)
		cout << "error accept(): " << WSAGetLastError() << endl;

	while (1)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));

		if (send(client, msg, strlen(msg), 0) == SOCKET_ERROR)
			cout << "error send(): " << WSAGetLastError() << endl;

		if(recv(client, recvbuf, 256,0) == SOCKET_ERROR)
			cout << "error recv(): " << WSAGetLastError() << endl;
		else
		{
			cout << "server recive: " << recvbuf << endl;
		}
	}

	closesocket(client);
	closesocket(slisten);
	WSACleanup();
}


void client()
{
	char sendbuf[256];
	char recvbuf[256];


	// Init WISOCK
	WSADATA wsData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsData) != 0)
		cout << "error WSAStartup(): " << WSAGetLastError() << endl;

	SOCKET sConnect;

	sConnect = socket(AF_INET, SOCK_STREAM, 0);
	if (sConnect == INVALID_SOCKET)
		cout << "error socket(): " << WSAGetLastError() << endl;


	sockaddr_in compar;
	compar.sin_addr.s_addr = inet_addr("127.0.0.1");
	compar.sin_family = AF_INET;
	compar.sin_port = htons(PORT);
	int infoLeng = sizeof(compar);

	if (connect(sConnect, (struct sockaddr*)&compar, infoLeng) == SOCKET_ERROR)
		cout << "error connect(): " << WSAGetLastError() << endl;

	while (true)
	{
		memset(&sendbuf, 0, sizeof(sendbuf));
		memset(&recvbuf, 0, sizeof(recvbuf));

		if(recv(sConnect,recvbuf, 256, 0) == SOCKET_ERROR)
			cout << "error recv(): " << WSAGetLastError() << endl;
		else
		{
			cout << "client recive: " << recvbuf << endl;
		}

		cout << "send: ";
		cin.getline(sendbuf, 256);

		if (send(sConnect,sendbuf,strlen(sendbuf),0) == SOCKET_ERROR)
			cout << "error send(): " << WSAGetLastError() << endl;
	}

	closesocket(sConnect);
	WSACleanup();

}

int main()
{
	cout << "Hello CMake." << endl;

	std::thread tServer(serveur);
	std::thread tClient(client);
	tServer.join();
	tClient.join();

	return 0;
}
