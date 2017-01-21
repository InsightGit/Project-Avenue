#include "ImagineNetwork.hpp"
#include "ImagineWaitRoom.hpp"
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
		 connectionStatus = connectionSocket.connect("192.168.1.99", 59000);
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
			if (connectionSocket.receive(recievedPacket) != sf::Socket::Done) {
				error = 3;
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
						sf::Socket::Status connectionStatus = connectionSocket.connect("192.168.1.99", 59001);
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
	sf::Packet recievedPacket;
	std::string message;
	while (!serverReady && error==0) {
		if (connectionSocket.receive(recievedPacket) != sf::Socket::Done) {
			if (recievedPacket >> message) {
				if (message == "ready") {
					serverReady == true;
				}
			}
		}
	}
}

imagineNetwork::imagineNetwork(sf::Font fontToUse, const char *IpAddress, const int port) {
#ifdef DEBUG
	std::cout << "Bound to " connectionSocket.getLocalPort() << "\n";
#endif // DEBUG
	fontToUse = defaultFont;
}

void imagineNetwork::whenReady(){
	if (error == 0) {
		sf::Packet packetToSend;
		packetToSend << std::string("ready");
		connectionSocket.send(packetToSend);
		waitRoom.readyLight.setTexture(waitRoom.landTextures[1]);
	}
}
