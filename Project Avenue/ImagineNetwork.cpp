#include "ImagineNetwork.hpp"
#include "ImagineWaitRoom.hpp"
#include "Player.hpp"
#include <stdexcept>
#include <thread>
#include <iostream>
/*std::thread imagineNetwork::callConnectingThread() {
	return std::thread([&](imagineNetwork imagine()) {imagine->connectingThread();});
}*/

void imagineNetwork::connectingThread() {
	connecting = true;
	sf::Socket::Status connectionStatus;
	std::cout << "Connecting...\n";
	if (!connection) {
		 connectionStatus = connectionSocket.connect("avenue.infernostudios.me", 59000);
		if (connectionStatus != sf::Socket::Done) {
			error = 1;
			connectionSocket.disconnect();
			std::cout << "Could not connect to Online Services!\n";
		}
	}
	if (connectionStatus==sf::Socket::Done || connection){
		sf::Packet recievedPacket;
		std::string message;
		std::string secondMessage;
		while (!waitRoomReady) {
			socketOccupied = true;
			if (connectionSocket.receive(recievedPacket) != sf::Socket::Done) {
				error = 3;
				socketOccupied = false;
				connectionSocket.disconnect();
				std::cout << "Could not recieve data from Online Services!\n";
			}
			std::cout << "DEBUG: 1:" << message << "\n";
			if (recievedPacket >> message) {
				if (message == "Connected") {
					connected = true;
					sf::Packet sendingPacket;
					sendingPacket << std::string("moreinfo");
					connectionSocket.send(sendingPacket);
				}
				else if (message == "waitroom1") {
					*waitRoomId = message;
					waitRoom = imagine::waitRoom("", defaultFont, message);
					error = 0; //this is not a error
					connection = false;
					waitRoomReady = true;
				}
				else if (message == "Full") {
					if (!connection) {
						connectionSocket.disconnect();
						sf::Socket::Status connectionStatus = connectionSocket.connect("avenue.infernostudios.me", 59001);
						if (connectionStatus != sf::Socket::Done) {
							error = 4;
							connectionSocket.disconnect();
							std::cout << "Could not connect to Online Services!\n";
						}
						else if (connectionStatus == sf::Socket::Done) {
							connection = true;
							connectingThread();
						}
					}
					else {
						error = 5;
						connectionSocket.disconnect();
						std::cout << "Could not connect to Online Services!\n";
					}
				}
			}
			else {
				error = 2;
				connectionSocket.disconnect();
			}
		}
	}
}

void imagineNetwork::updateServerStatus() {
	sf::Packet packetToRecieve;
	sf::Packet packetToSend;
	std::string message;
	while (!serverReady && error==0) {
		if (!socketOccupied) {
			socketOccupied = true;
			if (connectionSocket.receive(packetToRecieve) == sf::Socket::Done) {
				if (packetToRecieve >> message) {
					if (message == "ready") {
						packetToSend << std::string("ok");
						if (connectionSocket.send(packetToSend) != sf::Socket::Done) {
							connectionSocket.disconnect();
							*sceneNum = 0;
						}
						serverReady == true;
						std::cout << "SERVER IS READY!\n";
					}
				}
			}
			else {
				connectionSocket.disconnect();
				*sceneNum = 0;
			}
			socketOccupied = false;
		}	
	}
}

imagineNetwork::imagineNetwork(sf::Font fontToUse, player *mainPlayer, int *mainSceneNum, const char *IpAddress, const int port) {
	sceneNum = mainSceneNum;
#ifdef DEBUG
	std::cout << "Bound to " connectionSocket.getLocalPort() << "\n";
#endif // DEBUG
	fontToUse = defaultFont;
	player1 = mainPlayer;
}

void imagineNetwork::whenReady(){
	if (error == 0) {
		sf::Packet packetToSend;
		packetToSend << std::string("ready");
		socketOccupied = true;
		if (connectionSocket.send(packetToSend) != sf::Socket::Done) {
			*sceneNum = 0;
		}
		else {
			waitRoom.readyLight.setTexture(waitRoom.landTextures[1]);
		}
		socketOccupied = false;
	}
}

void imagineNetwork::arenaLoadingThread() {
	sf::Packet recievedPacket;
	std::string message;
	arenaLoading = true;
	if (serverReady) {
		socketOccupied = true;
		if (connectionSocket.receive(recievedPacket) == sf::Socket::Done) {
			if (recievedPacket >> message) {
				*arenaId = message;
				arenaLoaded = true;
			}
		}
		socketOccupied = false;
	}
}

void imagineNetwork::playerInfoThread() {
	sf::Packet packetToSend;
	sf::Packet packetRecieved;
	float player2x;
	float player2y;
	std::string message;
	if (arenaLoaded) {
		while (gameOn) {
			packetToSend << player1->playerRect.getPosition().x << player1->playerRect.getPosition().y;
			socketOccupied = true;
			if (connectionSocket.send(packetToSend) != sf::Socket::Done) {
				throw std::runtime_error("Could not send packet to server");
			}
			if (connectionSocket.receive(packetRecieved) != sf::Socket::Done) {
				throw std::runtime_error("Could not recieve packet from server");
			}
			socketOccupied = false;
			if (packetRecieved >> player2x >> player2y) {
				player2.playerRect.setPosition(sf::Vector2f(player2x,player2y));
			}
			else if (packetRecieved >> message) {
				if (message == "noinfo") {
					std::cout << "noinfo given!\n";
				}
			}
		}
	}
}