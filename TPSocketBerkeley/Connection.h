#pragma once
#include <WinSock2.h>
#include <iostream>

namespace uqac {
	namespace network {
		class Connection
		{
		public:
			Connection();
			~Connection();

			virtual void SendMsg(SOCKET outSock, std::string msg) {};
			virtual char* Receive(SOCKET sConnect) = 0;

		private:

		};
	}
}