#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include "ImagineWaitRoom.hpp"
#include "ImagineArena.hpp"
#include <thread>

class imagineNetwork {
public:
	sf::TcpSocket connectionSocket;
	sf::Socket::Status socketStatus;
	bool connected = false;
	bool ready = false;
	int error = -1;
	bool recievedInfo = false;
	bool connecting = false;
	bool waitRoomReady = false;
	bool serverReady = false;
	bool connection = false;
	bool arenaLoading = false;
	bool arenaLoaded = false;
	bool gettingInfo = false;
	bool gameOn = false;
	player *player1;
	player player2;
	std::string *waitRoomId = new std::string;
	std::string *arenaId = new std::string;
	imagine::waitRoom waitRoom;
	imagine::arena arena;

	sf::Font defaultFont;

	imagineNetwork(sf::Font fontToUse, player *mainPlayer, const char *IpAddress = "avenue.infernostudios.me", const int port = 59000);
	imagineNetwork();

	//virtual ~imagineNetwork();

	void updateServerStatus();
	bool isConnectionComplete();
	void whenReady();
//protected:
	void connectingThread();
	void arenaLoadingThread();
	void playerInfoThread();
	//givePosition

};