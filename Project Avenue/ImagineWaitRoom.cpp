#include "ImagineWaitRoom.hpp"
#include <stdexcept>

imagine::waitRoom::waitRoom(){}

imagine::waitRoom::waitRoom(std::string displayTextMessage, sf::Font fontToUse, std::string waitRoomId) {
	displayText.setString(displayTextMessage);
	displayText.setFont(fontToUse);
	id = waitRoomId;
}

void imagine::waitRoom::spawn(player *mainPlayer) {
	if (id == "waitroom1") {
		sf::RectangleShape landRect1 = sf::RectangleShape(sf::Vector2f(2000, 600));
		landRect1.setPosition(sf::Vector2f(-600, 700));
		landRect1.setFillColor(sf::Color::Green);
		landRects.push_back(landRect1);
		sf::Texture redLight;
		sf::Texture greenLight;
		if (!redLight.loadFromFile("Redlight.png")) {
			throw std::runtime_error("Could not load Redlight.png");
		}
		if(!greenLight.loadFromFile("Greenlight.png")) {
			throw std::runtime_error("Could not load Greenlight.png");
		}
		landTextures.push_back(redLight);
		landTextures.push_back(greenLight);
		readyLight.setPosition(mainPlayer->playerRect.getPosition().x, mainPlayer->playerRect.getPosition().y - 400);
		readyLight.setTexture(landTextures[0]);
		/*sf::RectangleShape landRect2 = sf::RectangleShape(sf::Vector2f(4000, 600));
		landRect1.setPosition(sf::Vector2f(-600, 700));
		landRect1.setFillColor(sf::Color::Green);
		landRects.push_back(landRect1);*/
	}
	spawned = true;
}

void imagine::waitRoom::updateView(player *mainPlayer) {
	waitRoomView.reset(sf::FloatRect(mainPlayer->playerRect.getPosition().x, mainPlayer->playerRect.getPosition().y, 1366, 768));
	waitRoomView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	waitRoomView.setCenter(mainPlayer->playerRect.getPosition());
	readyLight.setPosition(mainPlayer->playerRect.getPosition().x, mainPlayer->playerRect.getPosition().y - 400);
}
