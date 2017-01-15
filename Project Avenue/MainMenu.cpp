#include "MainMenu.hpp"
#include <random>

mainMenu::mainMenu(sf::Font defaultFont) {
	font = defaultFont;
	titleText.setFont(font);
	startGame.setFont(font);
	titleText.setString("Project Avenue");
	startGame.setString("1-player");
	titleText.setPosition(sf::Vector2f(512, 50));
	startGame.setPosition(sf::Vector2f(450, 325));
	activeCircle.setFillColor(sf::Color::Color(0, 0, 0));
	activeCircle.setPosition(sf::Vector2f(startGame.getPosition().x-150,startGame.getPosition().y));

	multiplayer.setFont(font);
	multiplayer.setString("2-player online race");
	multiplayer.setPosition(sf::Vector2f(startGame.getPosition().x, startGame.getPosition().y+100));
	titleText.setCharacterSize(30);
	titleText.setStyle(sf::Text::Regular);
	titleText.setFillColor(sf::Color::Black);

	titleText.setCharacterSize(50);
	startGame.setCharacterSize(30);
	titleText.setStyle(sf::Text::Regular);
	startGame.setStyle(sf::Text::Regular);
	titleText.setFillColor(sf::Color::Black);
	startGame.setFillColor(sf::Color::Black);
}

void mainMenu::update() {
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, 5);

	auto randomInt = uni(rng);
	activeCircle.setFillColor(sf::Color(activeCircle.getFillColor().r+randomInt, activeCircle.getFillColor().g, activeCircle.getFillColor().b));
	randomInt = uni(rng);
	activeCircle.setFillColor(sf::Color(activeCircle.getFillColor().r, activeCircle.getFillColor().g + randomInt, activeCircle.getFillColor().b));
	randomInt = uni(rng);
	activeCircle.setFillColor(sf::Color(activeCircle.getFillColor().r, activeCircle.getFillColor().g, activeCircle.getFillColor().b + randomInt));

	/*if (activeCircle.getFillColor().r > 255 && activeCircle.getFillColor().g > 255) {
		activeCircle.setFillColor(sf::Color::Color(0, activeCircle.getFillColor().g, activeCircle.getFillColor().b));
	}
	else if (activeCircle.getFillColor().g > 255 && activeCircle.getFillColor().b > 255) {
		activeCircle.setFillColor(sf::Color::Color(activeCircle.getFillColor().r, 0, activeCircle.getFillColor().b));
	}
	else if (activeCircle.getFillColor().b > 255 && activeCircle.getFillColor().r > 255) {
		activeCircle.setFillColor(sf::Color::Color(activeCircle.getFillColor().r, activeCircle.getFillColor().g, 0));
	}*/
	activeCircle.setPosition(sf::Vector2f(activeCircle.getPosition().x,225 + activePosition * 100));
}

void mainMenu::move(imagine::types::menuDirection direction) {
	if (direction == imagine::types::Up) {
		if (!activePosition <= 1) {
			activePosition--;
		}
	}
	else if (direction == imagine::types::Down) {
		if (activePosition < optionSize) {
			activePosition++;
		}
	}

}