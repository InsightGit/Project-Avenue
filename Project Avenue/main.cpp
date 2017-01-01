#include "Level.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(1366, 768), "Project Avenue", sf::Style::Fullscreen);
	sf::Font defaultFont;
	sf::Texture background;
	sf::Sprite backgroundSprite;
	player player1(sf::Vector2f(500,600));
	weapon weapon1(1);
	int sceneNum = 0;
	bool deletedMainMenu = false;

	if (!defaultFont.loadFromFile("default.ttf")) {
		return 1;
	}
	level level1("level1.txt",defaultFont,&player1);


	if (!background.loadFromFile("background.png")) {
		return 2;
	}

	backgroundSprite.setTexture(background);
	backgroundSprite.setPosition(sf::Vector2f(0, 0));
	mainMenu *mainM = new mainMenu(defaultFont);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized) {
				sf::FloatRect screenArea(0, 0, event.size.width, event.size.height);
				window.setView(sf::View(screenArea));
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			sceneNum = 1;
			//delete[] mainM;
			//deletedMainMenu = true;
		}
		window.clear();

		std::cout << sceneNum << "\n";
		if (sceneNum == 0) {
			window.draw(backgroundSprite);
			window.draw(mainM->titleText);
			window.draw(mainM->startGame);
		}
		else if (sceneNum == 1) {
			if (level1.subscene==0) {
				window.draw(level1.initalText);
				window.draw(level1.heartSprite);
				window.draw(level1.initalHeartText);
			}
			else {
				window.setView(level1.levelView);
				window.draw(backgroundSprite);
			}
		}
		else {
			std::cout << sceneNum << "\n";
			return 3;
		}
		window.display();
	}
	return 0;
}