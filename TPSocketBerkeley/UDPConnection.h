#pragma once
#include "Connection.h"

namespace uqac {
	namespace network {
		class UDPConnection : public Connection
		{
		public:

			void SendMsg(SOCKET outSock, std::string msg) override;
			char* Receive(SOCKET sConnect) override;

		private:

		};
	}
}