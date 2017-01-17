#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class imagineNetwork {
public:
	sf::TcpSocket connectionSocket;
	sf::Socket::Status socketStatus;
	bool *connected = new bool(false);
	bool *ready = new bool(false);
	int *error = new int(-1);
	bool *recievedInfo = new bool(false);
	std::string *waitRoomToLoad = new std::string;

	sf::Text displayText;
	sf::Font defaultFont;

	imagineNetwork(sf::Font fontToUse,const char *IpAddress = "192.168.1.99", const int port = 59000);

	virtual ~imagineNetwork();
	
	void connectingThread(const char *IpAddress, const int port);
	bool isConnectionComplete();
	void whenReady();
	//givePosition

};