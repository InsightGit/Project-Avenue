#pragma once
#include <SFML\Graphics.hpp>

class mainMenu{
	public:
	sf::Font font;
	sf::Text titleText;
	sf::Text startGame;

	mainMenu(sf::Font defaultFont);
};