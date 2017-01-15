#pragma once
#include <SFML/Graphics.hpp>
#include "ImagineTypes.hpp"

class mainMenu{
	public:
	sf::Font font;
	sf::Text titleText;
	sf::Text startGame;
	sf::Text multiplayer;
	sf::View mainMenuView = sf::View(sf::FloatRect(0, 76800, 1366, 768));
	sf::CircleShape activeCircle = sf::CircleShape(30);
	int activePosition = 1;
	int optionSize = 2;

	mainMenu(sf::Font defaultFont);

	void update();
	void move(imagine::types::menuDirection direction);
};