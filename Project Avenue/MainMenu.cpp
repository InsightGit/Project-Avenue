#include "MainMenu.hpp"

mainMenu::mainMenu(sf::Font defaultFont) {
	font = defaultFont;
	titleText.setFont(font);
	startGame.setFont(font);
	titleText.setString("Project Avenue");
	startGame.setString("Start");
	titleText.setPosition(sf::Vector2f(512, 50));
	startGame.setPosition(sf::Vector2f(450, 425));
	titleText.setCharacterSize(50);
	startGame.setCharacterSize(30);
	titleText.setStyle(sf::Text::Regular);
	startGame.setStyle(sf::Text::Regular);
	titleText.setFillColor(sf::Color::Black);
	startGame.setFillColor(sf::Color::Black);
}