#include "LibNetwork.h"

#pragma comment(lib, "ws2_32.lib")

#include <thread>
#include <cstdio>
#include <WinSock2.h>
#include <Windows.h>
using namespace std;

#include "Connection.h"

namespace uqac {
	namespace network {

		LibNetwork::LibNetwork()
		{
			Initialise();
		}

		LibNetwork::~LibNetwork()
		{
		}

		void LibNetwork::Initialise()
		{
			bool isServer = false;
			string respond;

			cout << "Initialise as Server (y/n)\n";
			cin >> respond;
			if (respond == "y" || respond == "yes")
				isServer = true;

			cout << "Use UDP on LOCAL HOST? (y/n)\n";
			cin >> respond;

			if (respond == "y" || respond == "yes") {
				if (isServer)
					Listen();
				else
					Connect();
			}
			else if (respond == "n" || respond == "no")
			{
				// configurer a la main
			}
			else
			{
				Initialise();
				return;
			}
		}

		void LibNetwork::Listen()
		{
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
			info.sin_port = htons(port);
			int infoLeng = sizeof(info);

			if (bind(slisten, (struct sockaddr*)&info, infoLeng) == SOCKET_ERROR)
				cout << "error bind(): " << WSAGetLastError() << endl;


			sockaddr_in clientInfo;
			int clientInfoLeng = sizeof(clientInfo);

			client = accept(slisten, (struct sockaddr*)&clientInfo, &clientInfoLeng);
			if (client == SOCKET_ERROR)
				cout << "error accept(): " << WSAGetLastError() << endl;

			//Connection* connect = new Connection();

			//std::thread tServer(connect);

			closesocket(client);
			closesocket(slisten);
			WSACleanup();
		}

		void LibNetwork::Connect()
		{
		}
	}
}