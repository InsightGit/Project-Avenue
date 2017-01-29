#include "ImagineSubMenu.hpp"

imagine::subMenu::subMenu(sf::Font currentFont, sf::View *currentView) {
	windowView = currentView;
	defaultFont = currentFont;
	position = sf::Vector2f(currentView->getCenter().x-150, currentView->getCenter().y - 150);
	miniScreen.setPosition(position);
	miniScreen.setFillColor(sf::Color::Black);
	//fadedBackgroudTexture

	continueText.setFont(defaultFont);
	continueText.setString("Continue");
	continueText.setPosition(sf::Vector2f(position.x+100,position.y+100));
	continueText.setCharacterSize(20);
	continueText.setStyle(sf::Text::Regular);
	continueText.setFillColor(sf::Color::White);

	returnText.setFont(defaultFont);
	returnText.setString("Return to Main Menu");
	returnText.setPosition(sf::Vector2f(position.x + 100, position.y + 200));
	returnText.setCharacterSize(15);
	returnText.setStyle(sf::Text::Regular);
	returnText.setFillColor(sf::Color::Red);

	activeCircle.setPosition(sf::Vector2f(position.x + 10, position.y + 100));
}

void imagine::subMenu::move(imagine::types::menuDirection direction) {
	if (direction == imagine::types::Up) {
		if (activePosition != 1) {
			activeCircle.move(sf::Vector2f(0, -100));
			activePosition--;
		}
	}
	else if (direction == imagine::types::Down) {
		if (activePosition < optionSize) {
			activeCircle.move(sf::Vector2f(0, 100));
			activePosition++;
		}
	}

}
