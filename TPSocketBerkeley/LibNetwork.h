#pragma once
#include <iostream>

namespace uqac {
	namespace network {

		class LibNetwork
		{
		public:
			LibNetwork();
			~LibNetwork();

			std::string protocol = "UDP";
			std::string ip = "192.168.2.12";
			int port = 25565;


			void Listen();
			void Connect();
		};
	}
}