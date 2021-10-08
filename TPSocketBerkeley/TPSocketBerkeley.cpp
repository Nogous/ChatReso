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
using namespace uqac::network;

void OnReceiveMsg(std::string s)
{
	
	cout << "receive : "<<s.c_str() << endl;
}

void StartServer(std::unique_ptr<uqac::network::LibNetwork> ptr) {
	ptr->Listen();
}
void StartClient(std::unique_ptr<uqac::network::LibNetwork> ptr) {

	std::function<void(std::string)> callback;
	callback = OnReceiveMsg;

	ptr->Connect(callback);
}


int main(int argc, char* argv[])
{
	if (argc == 5)
	{
		std::unique_ptr<LibNetwork> lib(new LibNetwork(string(argv[2]), string(argv[3]), atoi(argv[4])));
	
		if (argv[1] == string("server"))
		{
			std::thread tServer(StartServer, std::move(lib));
			cout << "Server launch" << endl;
			tServer.join();
		}
		else if (argv[1] == string("client"))
		{
			std::thread tClient(StartClient, std::move(lib));
			cout << "client launch" << endl;
			tClient.join();
		}
		else
		{
			return EXIT_FAILURE;
		}
	}
	else
	{
		std::unique_ptr<LibNetwork> lib(new LibNetwork());
		std::thread tClient(StartClient, std::move(lib));
		cout << "client launch" << endl;
		tClient.join();
	}
	return 0;
}
