#pragma once
#include <WinSock2.h>

namespace uqac {
	namespace network {
		class Terminal
		{
		public:
			Terminal();
			~Terminal();

			SOCKET Accept(SOCKET slisten);

		private:
			SOCKET client;
		};
	}
}