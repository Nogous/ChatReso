// TPSocketBerkeley.cpp : définit le point d'entrée de l'application.
//

#pragma comment(lib, "ws2_32.lib")

#include "TPSocketBerkeley.h"
#include <cstdio>
#include <iostream>
#include <WinSock2.h>
#include <Windows.h>
#include "LibNetwork.h"
using namespace std;


void StartServer(std::unique_ptr<uqac::network::LibNetwork> ptr) {
	ptr->Listen();
}
void StartClient(std::unique_ptr<uqac::network::LibNetwork> ptr) {
	ptr->Connect();
}

int main(int argc, char* argv[])
{
	char s[256];

	cout << "is server (y/n)" << endl;
	cin.getline(s, 256);
	string s2(s);

	std::unique_ptr<uqac::network::LibNetwork> lib(new uqac::network::LibNetwork());

	if (s2 == "y")
	{
		std::thread tServer(StartServer, std::move(lib));
		cout << "Server launch" << endl;
		tServer.join();
	}
	else
	{
		std::thread tClient(StartClient, std::move(lib));
		cout << "client launch" << endl;
		tClient.join();
	}

	return 0;
}
