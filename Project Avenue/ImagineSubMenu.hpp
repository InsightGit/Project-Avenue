#pragma once
#include "ImagineTypes.hpp"
#include <SFML/Graphics.hpp>

namespace imagine {
	class subMenu {
	public:
		sf::Font defaultFont;
		sf::Vector2f position; // usually set at center of screen
		sf::View *windowView;
		sf::Sprite fadedBackground;
		sf::Texture fadedBackgroudTexture;
		sf::Text continueText;
		sf::Text returnText;
		sf::CircleShape activeCircle = sf::CircleShape(25);
		sf::RectangleShape miniScreen = sf::RectangleShape(sf::Vector2f(300, 300));

		int activePosition = 1;
		int optionSize = 2;

		subMenu(sf::Font font,sf::View *currentView);

		void imagine::subMenu::move(imagine::types::menuDirection direction);
	};
}