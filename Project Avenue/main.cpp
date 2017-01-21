#include "Level.hpp"
#include "MainMenu.hpp"
#include "Player.hpp"
#include "Weapon.hpp"
#include "ImagineTypes.hpp"
#include "ImagineNetwork.hpp"
#include <iostream>
#include <thread>
#include <chrono>
#include <cstdio>
#include <cmath>
#include <stdexcept>
typedef std::chrono::high_resolution_clock Clock;

void threadPlaceholder() {
	std::cout << "Initlized thread\n";
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(136600, 76800), "Project Avenue",sf::Style::Fullscreen);
	sf::Font defaultFont;
	sf::Sound lostLifesound;
	sf::SoundBuffer coinCollectBuffer;
	if (!coinCollectBuffer.loadFromFile("CoinPickup.ogg")) {
		return 5;
	}
	sf::SoundBuffer lostLifeBuffer;
	if (!lostLifeBuffer.loadFromFile("lostLife.ogg")) {
		return 6;
	}
	//sf::Texture background;
	//sf::Sprite backgroundSprite;
	player player1(sf::Vector2f(170,600));
	weapon weapon1(1);
	imagineNetwork *network = new imagineNetwork(defaultFont);
	int sceneNum = 0;
	int playerIntersectCount = 0;
	int pastPosFrameCount = 0;
	bool deletedMainMenu = false;
	bool jumping = false;
	bool firstReadyTime = true;
	//bool movingRightPermitted = true;
	//bool movingLeftPermitted = true;
	bool firstTimeSpawn = true;
	sf::Clock clock;
	sf::Vector2f pastPos;
	float timer = 0;

	if (!defaultFont.loadFromFile("default.ttf")) {
		return 1;
	}
	level level1("level1.txt",defaultFont,&player1);
	player1.currentLevel = &level1;

	//if (!background.loadFromFile("background.png")) {
		//return 2;
	//}

	//backgroundSprite.setTexture(background);
	//backgroundSprite.setPosition(sf::Vector2f(0, 0));
	mainMenu *mainM = new mainMenu(defaultFont);
	std::clock_t timerStart = std::clock();
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

		pastPos = player1.playerRect.getPosition();

		if (sceneNum == 1 && level1.subscene == 1) {
			if (!level1.levelFinished) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					if (player1.movingLeftPermitted) {
						player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x - player1.walkSpeed, player1.playerRect.getPosition().y));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					if (player1.movingRightPermitted) {
						player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x + player1.walkSpeed, player1.playerRect.getPosition().y));
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
					if (!jumping) {
						player1.positionBeforeJump = player1.playerRect.getPosition();
						player1.jumpState = 0;
						timer = 1.0f;
						player1.jump(&timer, &playerIntersectCount);
						jumping = true;
					}
				}
			}
		}
		else if (sceneNum == 2 && network->waitRoomReady && network->connected && !network->serverReady) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
				if (player1.movingLeftPermitted) {
					player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x - player1.walkSpeed, player1.playerRect.getPosition().y));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if (player1.movingRightPermitted) {
					player1.playerRect.setPosition(sf::Vector2f(player1.playerRect.getPosition().x + player1.walkSpeed, player1.playerRect.getPosition().y));
				}
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
				if (!jumping) {
					player1.positionBeforeJump = player1.playerRect.getPosition();
					player1.jumpState = 0;
					timer = 1.0f;
					player1.jump(&timer, &playerIntersectCount);
					jumping = true;
				}
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
				network->whenReady();
			}
		}
		if (sceneNum == 0) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				mainM->move(imagine::types::Up);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				mainM->move(imagine::types::Down);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
				if (mainM->activePosition == 1) {
					sceneNum = 1;
				}
				else if (mainM->activePosition == 2) {
					sceneNum = 2;
				}
				//delete[] mainM;
				//deletedMainMenu = true;
			}
		}

		if (player1.jumpState == 2) {
			jumping = false;
		}
		if (jumping) {
			timer -= clock.getElapsedTime().asSeconds()*1500;
			player1.jump(&timer, &playerIntersectCount);
		}
		

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad9)) {
			level1.subscene = 1;
			//delete[] mainM;
			//deletedMainMenu = true;
		}
		window.clear(sf::Color::Color(20,146,210,1));

		//std::cout << sceneNum << "\n";
		if (sceneNum == 0) {
			//window.draw(backgroundSprite);
			window.setView(mainM->mainMenuView);
			mainM->mainMenuView.setCenter(sf::Vector2f(684,384));
			window.draw(mainM->titleText);
			window.draw(mainM->startGame);
			window.draw(mainM->activeCircle);
			window.draw(mainM->multiplayer);
			mainM->update();
			if (weapon1.owner == NULL) {
				player1.possessWeapon(&weapon1);
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
				if (!level1.levelSpawned) {
					if (level1.spawn(&player1) != 0) {
						return 4;
					}
				}
			}
			else if (level1.subscene==1){
				if (firstTimeSpawn) {
					level1.levelTime = sf::Clock();
					firstTimeSpawn = false;
					std::clock_t timerStart = std::clock();
				}
				//using views
				window.clear(sf::Color::Color(20, 146, 210, 1));
				level1.update(&player1);
				level1.updateView(player1,window.mapCoordsToPixel(player1.playerRect.getPosition(),level1.levelView));
				level1.levelView.setCenter(player1.playerRect.getPosition());

				window.setView(level1.levelView);

				playerIntersectCount = 0;
				for (int i = 0; level1.landRectShapesSize > i; i++) {
					if (i == 5) {
						break;
					}
					if (player1.playerRect.getGlobalBounds().intersects(level1.landRectShapes[i].getGlobalBounds())) {
						if (i == 0) {
							if (player1.playerRect.getPosition().y - 20 >= level1.landRectShapes[i].getPosition().y - 100) {
								playerIntersectCount++;
								player1.movingRightPermitted = true;
								player1.movingLeftPermitted = true;
							}
						}

						else {
							player1.movingRightPermitted = true;
							player1.movingLeftPermitted = true;
							if (player1.playerRect.getPosition().x - 20 <= level1.landRectShapes[i].getPosition().x /* && !player1.playerRect.getGlobalBounds().height > level1.landRectShapes[i].getGlobalBounds().height */) {
								//if (!player1.playerRect.getPosition().y > level1.landRectShapes[i].getGlobalBounds().height+1) {
								player1.movingRightPermitted = false;
								//}
							}
							if (player1.playerRect.getPosition().x - 20 >= level1.landRectShapes[i].getPosition().x /* && !player1.playerRect.getGlobalBounds().height > level1.landRectShapes[i].getGlobalBounds().height */) {
								player1.movingLeftPermitted = false;
							}
							if (player1.playerRect.getPosition().y - 20 >= level1.landRectShapes[i].getPosition().y - 100) {
								playerIntersectCount++;
							}
						}
					}
				}
				if (!player1.movingLeftPermitted && !player1.movingRightPermitted && player1.movingControlProtected) {
					player1.movingRightPermitted = true;
					player1.movingLeftPermitted = true;
				}
				if (player1.playerRect.getPosition().y > 850) {
					player1.lives--;
					lostLifesound.setBuffer(lostLifeBuffer);
					player1.playerRect.setPosition(sf::Vector2f(170, 600));
					lostLifesound.play();
				}

				for (int i = 0; level1.levelGems.size() > i; i++) {
					if (player1.playerRect.getGlobalBounds().intersects(level1.levelGems[i].gemSprite.getGlobalBounds())) {
						if (level1.levelGems[i].gemId != -858993460) {
							std::cout << "id=" << std::to_string(level1.levelGems[i].gemId);
						}
 						if (level1.levelGems[i].gemId == 2) {
							level1.levelGems[i].onCollect(&player1);
						}
						else {
							level1.levelGems[i].onCollect(&player1, &coinCollectBuffer);
						}
					}
				}


				if (playerIntersectCount == 0 && !jumping) {
					player1.playerRect.move(sf::Vector2f(0, player1.jumpSpeed));
				}

				player1.levelIntersectCount = playerIntersectCount;


				if (player1.playerRect.getPosition().x < 170) {
					player1.playerRect.setPosition(170, player1.playerRect.getPosition().y); //prevents players from seeing edge
				}
				if (player1.playerRect.getPosition().y < 0) {
					player1.playerRect.setPosition(player1.playerRect.getPosition().x, 170);
				}

				weapon1.update();
				window.draw(weapon1.weaponRect);
				window.draw(player1.playerRect);

				for (int i = 0; level1.landRectShapes.size() > i; i++) {
					window.draw(level1.landRectShapes[i]);
				}
				for (int i = 0; level1.levelEnemies.size() > i; i++) {
					double timerDuration = (std::clock() - timerStart) / (double)CLOCKS_PER_SEC;
					sf::Vector2f futurePos;
					sf::CircleShape futureCircle = level1.levelEnemies[i].enemyCircle;
					if (level1.levelEnemies[i].moving == 'l') {
						futurePos = sf::Vector2f(level1.levelEnemies[i].enemyCircle.getPosition().x - level1.levelEnemies[i].enemySpeed, level1.levelEnemies[i].enemyCircle.getPosition().y);
					}
					else if (level1.levelEnemies[i].moving == 'r') {
						futurePos = sf::Vector2f(level1.levelEnemies[i].enemyCircle.getPosition().x + level1.levelEnemies[i].enemySpeed, level1.levelEnemies[i].enemyCircle.getPosition().y);
					}

					futureCircle.setPosition(futurePos);

					//std::cout << timerDuration << "\n";
					if (i == 1) {
						break;
					}
					for (int c = 0; level1.landRectShapesSize > c; c++) {

						/*if (level1.levelEnemies[i].enemyCircle.getGlobalBounds().intersects(level1.landRectShapes[c].getGlobalBounds())) {
							level1.levelEnemies[i].update(true, futureCircle.getPosition());
						}
						else {
							level1.levelEnemies[i].update(false, futureCircle.getPosition());
						}*/
						if (futureCircle.getGlobalBounds().intersects(level1.landRectShapes[c].getGlobalBounds())) {
							level1.levelEnemies[i].update(true, futureCircle.getPosition());
							if (level1.levelEnemies[i].moving == 'l') {
								level1.levelEnemies[i].moving = 'r';
							}
							else if (level1.levelEnemies[i].moving == 'r') {
								level1.levelEnemies[i].moving == 'l';
							}
							level1.levelEnemies[i].limitDirectionChanges = true;
						}
						else {
							level1.levelEnemies[i].update(false, futureCircle.getPosition());
							level1.levelEnemies[i].limitDirectionChanges = true;
						}
					}
					futureCircle.move(0, 20);

					int enemyintersect = 0;
					for (int c = 0; level1.landRectShapesSize > c; c++) {
						if (futureCircle.getGlobalBounds().intersects(level1.landRectShapes[c].getGlobalBounds())) {
							enemyintersect++;
						}
					}
					if (enemyintersect == 0) {
						level1.levelEnemies[i].enemyCircle.move(sf::Vector2f(0, level1.levelEnemies[i].enemySpeed));
					}
					
					if (player1.playerRect.getGlobalBounds().intersects(level1.levelEnemies[i].enemyCircle.getGlobalBounds())) {
						player1.lives--;
						lostLifesound.setBuffer(lostLifeBuffer);
						player1.playerRect.setPosition(sf::Vector2f(170, 600));
						lostLifesound.play();
					}

					if (level1.levelEnemies[i].moving == 'l'  && timerDuration>=0.45) {
						level1.levelEnemies[i].enemyCircle.move(sf::Vector2f(level1.levelEnemies[i].enemySpeed / -1, 0));
						timerStart = std::clock();
					}
					else if (level1.levelEnemies[i].moving == 'r'  && timerDuration >= 0.45) {
						level1.levelEnemies[i].enemyCircle.move(sf::Vector2f(level1.levelEnemies[i].enemySpeed, 0));
						timerStart = std::clock();
					}
					window.draw(level1.levelEnemies[i].enemyCircle);
				}
				for (int i = 0; level1.levelGems.size() > i; i++) {
					window.draw(level1.levelGems[i].gemSprite);
				}				
				for (int i = 0; level1.levelQuestionBlock.size() > i; i++) {
					if (player1.playerRect.getGlobalBounds().intersects(level1.levelQuestionBlock[i].specialSprite.getGlobalBounds())) {
 						level1.levelQuestionBlock[i].onPlayerHit();
					}
					window.draw(level1.levelQuestionBlock[i].specialSprite);
				}
				for (int i = 0; level1.levelJumpPads.size() > i; i++) {
					if (level1.levelJumpPads[i].specialSprite.getGlobalBounds().intersects(player1.playerRect.getGlobalBounds())) {
						level1.levelJumpPads[i].onCollison(&player1);
					}
					window.draw(level1.levelJumpPads[i].specialSprite);
				}

				#ifdef _DEBUG
				std::cout << "PlayerPosition: (" << player1.playerRect.getPosition().x << "," << player1.playerRect.getPosition().y << ") Jumping:" << jumping << " PlayerIntersectCount:" << playerIntersectCount << "Position Before Jumping: (" << player1.positionBeforeJump.x << "," << player1.positionBeforeJump.y << ") Time:" << std::to_string(timer) << "\n";
				std::cout << "WeaponPosition: (" << weapon1.weaponRect.getPosition().x << "," << weapon1.weaponRect.getPosition().y << ")\n";
				#endif
				//Display HUD
				window.draw(level1.initalGemHUD);
				window.draw(level1.levelTimeHUD);
				window.draw(level1.heartSprite);

				window.draw(level1.initalGemText);
				window.draw(level1.initalHeartText);

				window.display();
				for (int i = 0; level1.levelEnemies.size() > i; i++) {
					level1.levelEnemies[i].limitDirectionChanges = false;
				}
			}
		}
		else if (sceneNum==2) {
			std::thread *connecting = new std::thread(threadPlaceholder);
			std::thread *checker = new std::thread(threadPlaceholder);
			sf::Text connectingText;
			if (!network->connected) {
				if (!network->connecting) {
					//connecting = new std::thread(&imagineNetwork::connectingThread,imagineNetwork());
					//connecting = &network.callConnectingThread();
					network->error = -1;
					connecting = new std::thread(&imagineNetwork::connectingThread,network);
				}
				if (network->error > 0) {
					sceneNum = 0;
				}
				connectingText.setFont(defaultFont);
				connectingText.setString("Connecting to Online Services...");
				connectingText.setPosition(sf::Vector2f(534, 344));
				connectingText.setCharacterSize(40);
				connectingText.setStyle(sf::Text::Regular);
				connectingText.setFillColor(sf::Color::Black);
				window.draw(connectingText);
			}
			else if (!network->waitRoomReady && network->connected) {
				connectingText.setString("Retriving info from Online Services...");
				window.draw(connectingText);
			}
			else if (network->waitRoomReady && network->connected && !network->serverReady) {
				if (!network->waitRoom.spawned) {
					network->waitRoom.spawn(&player1);
					checker = new std::thread(&imagineNetwork::updateServerStatus,network);
				}
				playerIntersectCount = 0;
				for (int i = 0; network->waitRoom.landRects.size() > i; i++) {
					if (i == 5) {
						break;
					}

					if (player1.playerRect.getGlobalBounds().intersects(network->waitRoom.landRects[i].getGlobalBounds())) {
						if (i == 0) {
							if (player1.playerRect.getPosition().y - 20 >= network->waitRoom.landRects[i].getPosition().y - 100) {
								playerIntersectCount++;
								player1.movingRightPermitted = true;
								player1.movingLeftPermitted = true;
							}
						}

						else {
							player1.movingRightPermitted = true;
							player1.movingLeftPermitted = true;
							if (player1.playerRect.getPosition().x - 20 <= network->waitRoom.landRects[i].getPosition().x /* && !player1.playerRect.getGlobalBounds().height > level1.landRectShapes[i].getGlobalBounds().height */) {
								//if (!player1.playerRect.getPosition().y > level1.landRectShapes[i].getGlobalBounds().height+1) {
								player1.movingRightPermitted = false;
								//}
							}
							if (player1.playerRect.getPosition().x - 20 >= network->waitRoom.landRects[i].getPosition().x /* && !player1.playerRect.getGlobalBounds().height > level1.landRectShapes[i].getGlobalBounds().height */) {
								player1.movingLeftPermitted = false;
							}
							if (player1.playerRect.getPosition().y - 20 >= network->waitRoom.landRects[i].getPosition().y - 100) {
								playerIntersectCount++;
							}
						}
					}
				}
				if (!player1.movingLeftPermitted && !player1.movingRightPermitted && player1.movingControlProtected) {
					player1.movingRightPermitted = true;
					player1.movingLeftPermitted = true;
				}
				if (player1.playerRect.getPosition().y > 850) {
					player1.lives--;
					lostLifesound.setBuffer(lostLifeBuffer);
					player1.playerRect.setPosition(sf::Vector2f(170, 600));
					lostLifesound.play();
				}

				/*for (int i = 0; level1.levelGems.size() > i; i++) {
					if (player1.playerRect.getGlobalBounds().intersects(level1.levelGems[i].gemSprite.getGlobalBounds())) {
						if (level1.levelGems[i].gemId != -858993460) {
							std::cout << "id=" << std::to_string(level1.levelGems[i].gemId);
						}
						if (level1.levelGems[i].gemId == 2) {
							level1.levelGems[i].onCollect(&player1);
						}
						else {
							level1.levelGems[i].onCollect(&player1, &coinCollectBuffer);
						}
					}
				}*/


				if (playerIntersectCount == 0 && !jumping) {
					player1.playerRect.move(sf::Vector2f(0, player1.jumpSpeed));
				}

				player1.levelIntersectCount = playerIntersectCount;


				if (player1.playerRect.getPosition().x < 170) {
					player1.playerRect.setPosition(170, player1.playerRect.getPosition().y); //prevents players from seeing edge
				}
				if (player1.playerRect.getPosition().y < 0) {
					player1.playerRect.setPosition(player1.playerRect.getPosition().x, 170);
				}

				window.setView(network->waitRoom.waitRoomView);
				network->waitRoom.updateView(&player1);

				window.draw(network->waitRoom.readyLight);
				window.draw(player1.playerRect);
				for (int i = 0; network->waitRoom.landRects.size() > i; i++) {
					window.draw(network->waitRoom.landRects[i]);
				}
			}
			
			window.display();
		}
		else {
			std::cout << sceneNum << "\n";
			return 3;
		}
		clock.restart();
	}
	return 0;
}