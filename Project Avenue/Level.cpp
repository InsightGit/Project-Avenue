#include "Level.hpp"
#include <stdexcept>

level::level(const std::string worldFileLocation,sf::Font defaultFont, player *player1) {
	initalFont = defaultFont;
	worldFile = std::ifstream(worldFileLocation);
	if (worldFile.is_open()) {
		std::string currentLine;
		while (getline(worldFile, currentLine)) {
			worldFileLines.push_back(currentLine);
		}
	}
	else {
		throw std::runtime_error("Could not open world file");
	}
	if (!heart.loadFromFile("heart.png")) {
		throw std::runtime_error("Could not open heart file");
	}
	if (worldFileLines[0] == "Level") {
		levelId = worldFileLines[1];
	}
	initalText.setFont(initalFont);
	initalText.setString("Level " + levelId);
	initalText.setPosition(sf::Vector2f(580, 50));
	initalText.setCharacterSize(40);
	initalText.setStyle(sf::Text::Regular);
	initalText.setFillColor(sf::Color::White);

	heartSprite.setTexture(heart);
	heartSprite.setPosition(sf::Vector2f(580, 500));

	initalHeartText.setFont(initalFont);
	initalHeartText.setString(std::to_string(player1->lives));
	initalHeartText.setPosition(sf::Vector2f(630, 565));
	initalHeartText.setCharacterSize(30);
	initalHeartText.setStyle(sf::Text::Regular);
	initalHeartText.setFillColor(sf::Color::White);
}
void level::updateView(player mainPlayer) {
	sf::Vector2f position(mainPlayer.playerRect.getPosition().x + 100, mainPlayer.playerRect.getPosition().y + 100);
	levelView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	levelView.reset(sf::FloatRect(position.x, position.y, 1366, 768));
	//levelView.reset(sf::FloatRect(0, 0, 1366, 768));
	levelView.setCenter(mainPlayer.playerPosition);
	if (mainPlayer.playerRect.getPosition().x < 0) {
		mainPlayer.playerRect.setPosition(0, mainPlayer.playerRect.getPosition().y);
	}
	if (mainPlayer.playerRect.getPosition().y < 0) {
		mainPlayer.playerRect.setPosition(mainPlayer.playerRect.getPosition().x,0);
	}
}