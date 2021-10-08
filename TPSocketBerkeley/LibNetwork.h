#pragma once
#include <iostream>
#include <functional>

namespace uqac::network {

	class LibNetwork
	{
	public:
		LibNetwork();
		LibNetwork(std::string desiredProtocol, std::string desiredIp, int desiredPort);
		~LibNetwork();

		std::string protocol = "UDP";
		std::string ip = "127.0.0.1";
		int port = 25565;


		void Listen();
		void Connect(std::function<void(std::string)> callback);
	};
}