#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "ImagineWaitRoom.hpp"
#include <thread>

static class imagineNetwork {
public:
	sf::TcpSocket connectionSocket;
	sf::Socket::Status socketStatus;
	bool connected = false;
	bool ready = false;
	int error = -1;
	bool recievedInfo = false;
	bool connecting = false;
	std::string *waitRoomId = new std::string;
	imagine::waitRoom waitRoom;

	sf::Font defaultFont;

	imagineNetwork(sf::Font fontToUse,const char *IpAddress = "192.168.1.99", const int port = 59000);
	imagineNetwork();

	//virtual ~imagineNetwork();

	std::thread callConnectingThread();
	bool isConnectionComplete();
	void whenReady();
//protected:
	void connectingThread();
	//givePosition

};