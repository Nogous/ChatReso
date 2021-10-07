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
			std::string ip = "127.0.0.1";
			int port = 80;


			void Listen();
			void Connect();

		private:
			void Initialise();
		};
	}
}