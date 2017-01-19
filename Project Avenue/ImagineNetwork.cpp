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
	std::cout << "Connecting...\n";
	sf::Socket::Status connectionStatus = connectionSocket.connect("192.168.1.99", 59000);
	if (connectionStatus != sf::Socket::Done) {
		error = 1;
		std::cout << "Could not connect to Online Services!\n";
	}
	else if (connectionStatus==sf::Socket::Done){
		sf::Packet recievedPacket;
		if (connectionSocket.receive(recievedPacket) != sf::Socket::Done) {
			error = 3;
			std::cout << "Could not recieve data from Online Services!\n";
		}
		std::string message;
		std::string secondMessage;
		while (!ready) {
			std::cout << "DEBUG: 1:" << message << "\n";
			if (recievedPacket >> message) {
				if (message == "Connected") {
					connected = true;
					sf::Packet sendingPacket;
					sendingPacket << std::string("moreinfo");
					connectionSocket.send(sendingPacket);
				}
			}
			else if (recievedPacket >> message >> secondMessage) {
				*waitRoomId = secondMessage;
				std::cout << "DEBUG: 1:" << message << " 2:" << secondMessage << "\n";
				waitRoom = imagine::waitRoom(message,defaultFont,secondMessage);
				error = 0; //this is not a error
			}
			else {
				error = 2;
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
	}
}
