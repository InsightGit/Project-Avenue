#pragma once
#include <SFML/Network.hpp>

class imagineNetwork {
public:
	sf::TcpSocket socket;
	sf::Socket::Status socketStatus;

	imagineNetwork(const char *IpAddress, const int port = 5900);
	
	//givePosition

};