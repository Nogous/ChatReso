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
	char recvbuf[4096];
	char* welcomMsg = "Connect to server\n";
	string msg;

	// Init WISOCK
	WSADATA wsData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsData) != 0)
		ExitProcess(EXIT_FAILURE);

	//creation des socket
	SOCKET slisten, client;

	//parametarge socket listen
	slisten = socket(AF_INET, SOCK_STREAM, 0);
	if (slisten == INVALID_SOCKET)
		cout << "error socket(): " << WSAGetLastError() << endl;

	// bind ip address and port
	sockaddr_in info;
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family = AF_INET;
	info.sin_port = htons(PORT);
	int infoLeng = sizeof(info);

	if (bind(slisten, (struct sockaddr*)&info, infoLeng) == SOCKET_ERROR)
		cout << "error bind(): " << WSAGetLastError() << endl;

	if (listen(slisten, SOMAXCONN) == SOCKET_ERROR)
		cout << "error listen(): " << WSAGetLastError() << endl;
	
	fd_set master;
	FD_ZERO(&master);

	FD_SET(slisten, &master);

	while (true)
	{
		fd_set copy = master;

		int socketCount = select(0, &copy, nullptr, nullptr, nullptr);

		for (int i = 0; i < socketCount; i++)
		{
			SOCKET sock = copy.fd_array[i];
			if (sock == slisten)
			{
				// accept a new connection
				sockaddr_in clientInfo;
				int clientInfoLeng = sizeof(clientInfo);

				client = accept(slisten, (struct sockaddr*)&clientInfo, &clientInfoLeng);
				if (client == SOCKET_ERROR)
					cout << "error accept(): " << WSAGetLastError() << endl;
				// Add new connection
				FD_SET(client, &master);
				// send welcome msg
				if (send(client, welcomMsg, strlen(welcomMsg), 0) == SOCKET_ERROR)
					cout << "error send(): " << WSAGetLastError() << endl;
			}
			else
			{
				// reset buffer
				memset(&recvbuf, 0, sizeof(recvbuf));

				// accept a new message
				int byteIn = recv(sock, recvbuf, 256, 0);

				if (byteIn <= 0)
				{
					// drop the client
					closesocket(sock);
					FD_CLR(sock, &master);
				}
				else
				{
					msg = recvbuf;
					msg = msg + "\n";

					// send message to other clients
					for (int i = 0; i < master.fd_count; i++)
					{
						SOCKET outSock = master.fd_array[i];
						if (outSock != slisten && outSock != sock)
						{
							if (send(outSock, msg.c_str(), strlen(msg.c_str()), 0) == SOCKET_ERROR)
								cout << "error send(): " << WSAGetLastError() << endl;
						}
					}
				}
			}
		}
	}

	// close socket
	closesocket(client);
	closesocket(slisten);
	// cleanup winsock
	WSACleanup();
}


void Receiver(SOCKET sConnect) {

	char recvbuf[256];

	while (true)
	{
		memset(&recvbuf, 0, sizeof(recvbuf));

		if (recv(sConnect, recvbuf, 256, 0) == SOCKET_ERROR)
			cout << "error recv(): " << WSAGetLastError() << endl;
		else
		{
			cout << "client recive: " << recvbuf << endl;
		}
	}
}

void client()
{
	// Init WISOCK
	WSADATA wsData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsData) != 0)
		cout << "error WSAStartup(): " << WSAGetLastError() << endl;

	// creat socket
	SOCKET sConnect;

	sConnect = socket(AF_INET, SOCK_STREAM, 0);
	if (sConnect == INVALID_SOCKET)
		cout << "error socket(): " << WSAGetLastError() << endl;

	// bind ip address and port
	sockaddr_in info;
	info.sin_addr.s_addr = inet_addr("127.0.0.1");
	info.sin_family = AF_INET;
	info.sin_port = htons(PORT);
	int infoLeng = sizeof(info);


	// connect to serveur
	if (connect(sConnect, (struct sockaddr*)&info, infoLeng) == SOCKET_ERROR)
	{
		cout << "error connect(): " << WSAGetLastError() << endl;

		closesocket(sConnect);
		WSACleanup();
		return;
	}

	std::thread receive(Receiver, sConnect);

	char sendbuf[256];

	while (true)
	{
		memset(&sendbuf, 0, sizeof(sendbuf));

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
	char s[256];

	cout << "is server (y/n)" << endl;
	cin.getline(s, 256);
	string s2(s);

	if (s2 == "2")
	{
		std::thread tServer(serveur);
		cout << "Server lonch" << endl;
		std::thread tClient(client);
		cout << "client lonch" << endl;
		tServer.join();
		tClient.join();
	}
	else if (s2 == "y")
	{
		std::thread tServer(serveur);
		cout << "Server lonch" << endl;
		tServer.join();
	}
	else
	{
		std::thread tClient(client);
		cout << "client lonch" << endl;
		tClient.join();
	}

	return 0;
}
