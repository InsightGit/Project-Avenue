#include "Level.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include <iostream>

int main()
{
	sf::RenderWindow window(sf::VideoMode(136600, 76800), "Project Avenue",sf::Style::Fullscreen);
	sf::Font defaultFont;
	//sf::Texture background;
	//sf::Sprite backgroundSprite;
	player player1(sf::Vector2f(100,600));
	weapon weapon1(1);
	int sceneNum = 0;
	bool deletedMainMenu = false;

	if (!defaultFont.loadFromFile("default.ttf")) {
		return 1;
	}
	level level1("level1.txt",defaultFont,&player1);

	//if (!background.loadFromFile("background.png")) {
		//return 2;
	//}

	//backgroundSprite.setTexture(background);
	//backgroundSprite.setPosition(sf::Vector2f(0, 0));
	mainMenu *mainM = new mainMenu(defaultFont);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::Resized && sceneNum == 1 && level1.subscene==1) {
				//sf::FloatRect screenArea(0, 0, event.size.width, event.size.height);
				//window.setView(sf::View(screenArea));
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x - player1.walkspeed, player1.playerRect.getPosition().y));
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x + player1.walkspeed, player1.playerRect.getPosition().y));
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
			sceneNum = 1;
			//delete[] mainM;
			//deletedMainMenu = true;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {
			level1.subscene = 1;
			//delete[] mainM;
			//deletedMainMenu = true;
		}
		window.clear(sf::Color::Color(20,146,210,1));

		std::cout << sceneNum << "\n";
		if (sceneNum == 0) {
			//window.draw(backgroundSprite);
			window.draw(mainM->titleText);
			window.draw(mainM->startGame);
			if (weapon1.owner == NULL) {
				player1.possessWeapon(weapon1);
			}
			window.display();
		}
		else if (sceneNum == 1) {
			if (level1.subscene==0) {
				window.clear(sf::Color::Color(20, 146, 210, 1));
				window.draw(level1.initalText);
				window.draw(level1.heartSprite);
				window.draw(level1.initalHeartText);
				window.display();
			}
			else if (level1.subscene==1){
				//using views
				window.clear(sf::Color::Color(20, 146, 210, 1));
				//window.draw(backgroundSprite);
				level1.updateView(player1,window.mapCoordsToPixel(player1.playerRect.getPosition(),level1.levelView));
				sf::Vector2f tempVar = player1.playerRect.getPosition();
				level1.levelView.setCenter(tempVar);
				window.setView(level1.levelView);
				window.draw(player1.playerRect);
				weapon1.update();
				window.draw(weapon1.weaponRect);
				window.display();
			}
		}
		else {
			std::cout << sceneNum << "\n";
			return 3;
		}

	}
	return 0;
}