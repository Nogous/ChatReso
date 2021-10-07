#pragma once
#include "UDPConnection.h"
#include <iostream>

namespace uqac {
	namespace network {

		class LibNetwork
		{
		public:
			LibNetwork();
			~LibNetwork();

			std::string protocol = "UDP";
			std::string ip = "127.0.0.1";
			int port = 80;

		private:
			void Initialise();
			void Listen();
			void Connect();
		};
	}
}