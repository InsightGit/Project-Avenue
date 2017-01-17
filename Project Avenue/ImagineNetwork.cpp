#include "ImagineNetwork.hpp"
#include <stdexcept>
#include <thread>
#include <iostream>
void imagineNetwork::connectingThread(const char *IpAddress, const int port) {
	if (connectionSocket.connect(IpAddress, port) != sf::Socket::Status::Done) {
		*error = 1;
	}
	else {
		sf::Packet recievedPacket;
		connectionSocket.receive(recievedPacket);
		std::string message;
		std::string secondMessage;
		while (!*ready) {
			if (recievedPacket >> message) {
				if (message == "Connected") {
					*connected = true;
					sf::Packet sendingPacket;
					sendingPacket << std::string("moreinfo");
					connectionSocket.send(sendingPacket);
				}
			}
			else if (recievedPacket >> message >> secondMessage) {
				displayText.setFont(defaultFont);
				displayText.setString(message);
				*waitRoomToLoad = secondMessage;
				*error = 0;
			}
			else {
				*error = 2;
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
	if (*error == 0) {
		sf::Packet packetToSend;
		packetToSend << std::string("ready");
		connectionSocket.send(packetToSend);
	}
}
