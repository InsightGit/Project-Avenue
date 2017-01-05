#include "Level.hpp"
#include "Gem.hpp"
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
void level::updateView(player mainPlayer,sf::Vector2i worldCoords) {
	sf::Vector2f worldCoordsFloat = sf::Vector2f(worldCoords);
	//sf::Vector2f position(mainPlayer.playerRect.getPosition().x, mainPlayer.playerRect.getPosition().y);
	levelView.reset(sf::FloatRect(mainPlayer.playerRect.getPosition().x, mainPlayer.playerRect.getPosition().y, 1366, 768));
	levelView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	//levelView.reset(sf::FloatRect(0, 0, 1366, 768));
	//if (mainPlayer.playerRect.getPosition().x > position.x) {
		//levelView.move(sf::Vector2f(mainPlayer.playerRect.getPosition().x-position.x+100,0));		
	//}
	//else if (mainPlayer.playerRect.getPosition().x < position.x) {
		//levelView.move(sf::Vector2f(mainPlayer.playerRect.getPosition().x-position.x-100, 0));
	//}
	//else if (mainPlayer.playerRect.getPosition().y > position.y) {
		//levelView.move(sf::Vector2f(0, mainPlayer.playerRect.getPosition().y - position.y + 100));
	//}
	//else if (mainPlayer.playerRect.getPosition().y < position.y) {
		//levelView.move(sf::Vector2f(0, mainPlayer.playerRect.getPosition().y - position.y - 100));
	//}
	//levelView.setCenter(worldCoordsFloat);

	//if (mainPlayer.playerRect.getPosition().x < 0) {                                 <- Included
		//mainPlayer.playerRect.setPosition(0, mainPlayer.playerRect.getPosition().y); <- in
	//}																				   <- main.cpp
	//if (mainPlayer.playerRect.getPosition().y < 0) {								   <-
		//mainPlayer.playerRect.setPosition(mainPlayer.playerRect.getPosition().x,0);  <-
	//}                                                                                <-
}

int level::spawn() {
	if (levelId == "1-1") {
		sf::RectangleShape landRect1 = sf::RectangleShape(sf::Vector2f(4000, 600));
		landRect1.setPosition(sf::Vector2f(-600, 700));
		landRect1.setFillColor(sf::Color::Green);
		landRectShapes.push_back(landRect1);
		landRectShapesSize++;

		sf::RectangleShape landRect2 = sf::RectangleShape(sf::Vector2f(100, 99));
		landRect2.setPosition(sf::Vector2f(400, 601));
		landRect2.setFillColor(sf::Color::Color(8, 253, 36, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect2);

		sf::RectangleShape landRect3 = sf::RectangleShape(sf::Vector2f(100, 199));
		landRect3.setPosition(sf::Vector2f(600, 501));
		landRect3.setFillColor(sf::Color::Color(8, 253, 36, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect3);

		enemy enemy1(1, sf::Vector2f(1500, 600));
		levelEnemies.push_back(enemy1);

		gem gem1(1, sf::Vector2f(1000,600));
		levelGems.push_back(gem1);

		levelTimeHUD.setFont(initalFont);
		levelTimeHUD.setPosition(sf::Vector2f(630, 565));
		levelTimeHUD.setCharacterSize(30);
		levelTimeHUD.setStyle(sf::Text::Regular);
		levelTimeHUD.setFillColor(sf::Color::White);

		if (int(levelTime.getElapsedTime().asSeconds()) % 60) {
			//minute time
			levelTimeHUD.setString(int(levelTime.getElapsedTime().asSeconds())/60 + ":" + std::to_string(levelTime.getElapsedTime().asSeconds()));
		}
		else {
			levelTimeHUD.setString("00:" + std::to_string(levelTime.getElapsedTime().asSeconds()));
		}

	}

	return 0;
}

void level::update(player *mainPlayer) {
	initalHeartText.setString(std::to_string(mainPlayer->lives));
	heartSprite.setPosition(sf::Vector2f(1300, 50));
	initalHeartText.setPosition(sf::Vector2f(1350, 115));
	if (int(levelTime.getElapsedTime().asSeconds()) % 60) {
		//minute time
		levelTimeHUD.setString(int(levelTime.getElapsedTime().asSeconds()) / 60 + ":" + std::to_string(levelTime.getElapsedTime().asSeconds()));
	}
	else {
		levelTimeHUD.setString("00:" + std::to_string(levelTime.getElapsedTime().asSeconds()));
	}
}

void level::onComplete(){}