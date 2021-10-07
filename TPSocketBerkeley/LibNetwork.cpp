#include "LibNetwork.h"

#pragma comment(lib, "ws2_32.lib")

#include <thread>
#include <cstdio>
#include <WinSock2.h>
#include <Windows.h>
using namespace std;

#include "Connection.h"
#include "TCPConnection.h"
#include "UDPConnection.h"
#include "Terminal.h"

namespace uqac {
	namespace network {

		LibNetwork::LibNetwork()
		{
			// Init WISOCK
			WSADATA wsData;
			WORD DllVersion = MAKEWORD(2, 1);
			if (WSAStartup(DllVersion, &wsData) != 0)
				ExitProcess(EXIT_FAILURE);

			//Initialise();
		}

		LibNetwork::~LibNetwork()
		{
			// cleanup winsock
			WSACleanup();
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
			Connection* connection;
			Terminal* terminal = new Terminal();

			//creation des socket
			SOCKET slisten;

			//parametarge socket listen
			slisten = socket(AF_INET, SOCK_STREAM, 0);
			if (slisten == INVALID_SOCKET)
				cout << "error socket(): " << WSAGetLastError() << endl;

			// bind ip address and port
			sockaddr_in info;
			info.sin_addr.s_addr = inet_addr(ip.c_str());
			info.sin_family = AF_INET;
			info.sin_port = htons(port);

			if (protocol == "TCP")
			{
				connection = new TCPConnection;
			}
			else
			{
				connection = new UDPConnection;
			}

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
						SOCKET client = terminal->Accept(slisten);

						// Add new connection
						FD_SET(client, &master);
					}
					else
					{
						char recvbuf[4096];
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
							string msg;
							msg = recvbuf;
							msg = msg + "\n";

							// send message to other clients
							for (int i = 0; i < master.fd_count; i++)
							{
								SOCKET outSock = master.fd_array[i];
								if (outSock != slisten && outSock != sock)
								{
									connection->SendMsg(outSock, msg);
								}
							}
						}
					}
				}
			}

			// close socket
			closesocket(slisten);
		}

		void Receiver(SOCKET sock) {

			Connection* connection = new TCPConnection;
			
			while (true)
			{
				cout << "client recive: " << connection->Receive(sock) << endl;
			}
		}

		void LibNetwork::Connect()
		{
			Connection* connection;

			// creat socket
			SOCKET sConnect;

			sConnect = socket(AF_INET, SOCK_STREAM, 0);
			if (sConnect == INVALID_SOCKET)
				cout << "error socket(): " << WSAGetLastError() << endl;

			// bind ip address and port
			sockaddr_in info;
			info.sin_addr.s_addr = inet_addr(ip.c_str());
			info.sin_family = AF_INET;
			info.sin_port = htons(port);
			int infoLeng = sizeof(info);

			if (protocol == "TCP")
			{
				connection = new TCPConnection;
			}
			else
			{
				connection = new UDPConnection;
			}

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

				connection->SendMsg(sConnect, sendbuf);
			}

			closesocket(sConnect);
		}


	}
}