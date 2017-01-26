#include "Level.hpp"
#include "Gem.hpp"
#include "JumpPad.hpp"
#include "QuestionBlock.hpp"
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

int level::spawn(player *playerInLevel) {
	levelFinished = false;
	if (levelId == "1-1") {
		sf::RectangleShape landRect1 = sf::RectangleShape(sf::Vector2f(4000, 600));
		landRect1.setPosition(sf::Vector2f(-600, 1700));
		landRect1.setFillColor(sf::Color::Green);
		landRectShapes.push_back(landRect1);
		landRectShapesSize++;

		sf::RectangleShape landRect2 = sf::RectangleShape(sf::Vector2f(100, 99));
		landRect2.setPosition(sf::Vector2f(600, 1601));
		landRect2.setFillColor(sf::Color::Color(8, 253, 36, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect2);

		sf::RectangleShape landRect3 = sf::RectangleShape(sf::Vector2f(100, 99));
		landRect3.setPosition(sf::Vector2f(1000, 1601));
		landRect3.setFillColor(sf::Color::Color(8, 253, 36, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect3);


		sf::RectangleShape landRect4 = sf::RectangleShape(sf::Vector2f(300,100));
		landRect4.setPosition(sf::Vector2f(1500, 1600));
		landRect4.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect4);
		

		sf::RectangleShape landRect5 = sf::RectangleShape(sf::Vector2f(300, 50));
		landRect5.setPosition(sf::Vector2f(3500, 1700));
		landRect5.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect5);

		sf::RectangleShape landRect6 = sf::RectangleShape(sf::Vector2f(200, 40));
		landRect6.setPosition(sf::Vector2f(3950, 1600));
		landRect6.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect6);


		sf::RectangleShape landRect7 = sf::RectangleShape(sf::Vector2f(150, 30));
		landRect7.setPosition(sf::Vector2f(4400, 1500));
		landRect7.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect7);
		
		sf::RectangleShape landRect8 = sf::RectangleShape(sf::Vector2f(200, 70));
		landRect8.setPosition(sf::Vector2f(2000, 1450));
		landRect8.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect8);

		sf::RectangleShape landRect9 = sf::RectangleShape(sf::Vector2f(100, 50));
		landRect9.setPosition(sf::Vector2f(2400, 1265));
		landRect9.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect9);

		sf::RectangleShape landRect10 = sf::RectangleShape(sf::Vector2f(500, 350));
		landRect10.setPosition(sf::Vector2f(4700, 1290));
		landRect10.setFillColor(sf::Color::Color(219, 220, 219, 100));
		landRectShapesSize++;
		landRectShapes.push_back(landRect10);

		jumpPad jumpPad1(1, sf::Vector2f(landRect7.getPosition().x+50, landRect7.getPosition().y-90));
		jumpPad1.specialSprite.setTexture(jumpPadTexture);
		levelJumpPads.push_back(jumpPad1);



		/*sf::RectangleShape landRect6 = sf::RectangleShape(sf::Vector2f(400, 100));
		landRect6.setPosition(sf::Vector2f(1500, 300));
		landRect6.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect6);

		sf::RectangleShape landRect7 = sf::RectangleShape(sf::Vector2f(200, 100));
		landRect7.setPosition(sf::Vector2f(1200, 400));
		landRect7.setFillColor(sf::Color::Color(120, 83, 23, 255));
		landRectShapesSize++;
		landRectShapes.push_back(landRect7);*/

		enemy enemy1(1, sf::Vector2f(2000, 1300));
		levelEnemies.push_back(enemy1);
		enemy enemy2(1, sf::Vector2f(2500, 1300));
		levelEnemies.push_back(enemy2);
		enemy enemy3(1, sf::Vector2f(3000, 1300));
		levelEnemies.push_back(enemy3);

		if (!gemTexture.loadFromFile("gem.png")) {
			throw std::runtime_error("Could not open gem texture file");
		}
		if (!finishGemTexture.loadFromFile("FinishGem.png")) {
			throw std::runtime_error("Could not open FinishGem.png texture file");
		}
		if (!jumpPadTexture.loadFromFile("jumpPad.png")) {
			throw std::runtime_error("Could not open jumpPad.png texture file");
		}
		if (!questionBlockTexture.loadFromFile("QuestionBlock.png")) {
			throw std::runtime_error("Could not open QuestionBlock.png texture file");
		}

		gem gem1(1, sf::Vector2f(1000,1600));
		gem1.gemSprite.setTexture(gemTexture);
		gem1.gemSprite.setScale(0.75, 0.75);
		levelGems.push_back(gem1);

		/*gem finishGem(2, sf::Vector2f(3000, 500));
		finishGem.gemSprite.setTexture(finishGemTexture);
		levelGems.push_back(finishGem);
		*/
		/*gem gemForQB1(1,sf::Vector2f(-1000,-1000));
		gemForQB1.gemSprite.setTexture(gemTexture);
		gemForQB1.gemSprite.setPosition(sf::Vector2f(1300, 299));*/

		/*questionBlock questionBlock1(&gemForQB1,sf::Vector2f(1300,299));
		questionBlock1.specialSprite.setTexture(questionBlockTexture);
		levelQuestionBlock.push_back(questionBlock1);*/

		levelTimeHUD.setFont(initalFont);
		levelTimeHUD.setPosition(sf::Vector2f(playerInLevel->playerRect.getPosition().x+400, playerInLevel->playerRect.getPosition().y-300));
		levelTimeHUD.setCharacterSize(30);
		levelTimeHUD.setStyle(sf::Text::Regular);
		levelTimeHUD.setFillColor(sf::Color::White);

		if (!initalGemHUDTexture.loadFromFile("gem.png")) {
			throw std::runtime_error("Could not open gem texture file");
		}
		initalGemHUD.setTexture(initalGemHUDTexture);
		initalGemHUD.setPosition(playerInLevel->playerRect.getPosition().x, playerInLevel->playerRect.getPosition().y - 300);
		initalGemText.setFont(initalFont);
		initalGemText.setString(std::to_string(playerInLevel->coinCount));
		initalGemText.setPosition(sf::Vector2f(initalGemHUD.getPosition().x+40, initalGemHUD.getPosition().y+30));
		initalGemText.setCharacterSize(30);
		initalGemText.setStyle(sf::Text::Regular);
		initalGemText.setFillColor(sf::Color::White);


		if (int(levelTime.getElapsedTime().asSeconds())/60 >= 1) {
			//minute time
			levelTimeHUD.setString(int(levelTime.getElapsedTime().asSeconds()/60) + ":" + std::to_string(levelTime.getElapsedTime().asSeconds()));
		}
		else {
			levelTimeHUD.setString("00:" + std::to_string(levelTime.getElapsedTime().asSeconds()));
		}

	}

	return 0;
}

void level::update(player *mainPlayer) {
	//heartSprite.setPosition(sf::Vector2f(1300, 50));
	//initalHeartText.setPosition(sf::Vector2f(1350, 115));
	if (int(levelTime.getElapsedTime().asSeconds()) >= 60) {
		//minute time
		int levelSecs = levelTime.getElapsedTime().asSeconds();
		if (levelSecs%60==0) {
			levelTimeHUDMinute = levelSecs / 60;
		}  
    		levelTimeHUD.setString(levelTimeHUDMinute + ":" + std::to_string(levelSecs));
	}
	else {
		if (int(levelTime.getElapsedTime().asSeconds() < 10)) {
			levelTimeHUD.setString("00:0" + std::to_string(int(levelTime.getElapsedTime().asSeconds())));
		}
		else {
			levelTimeHUD.setString("00:" + std::to_string(int(levelTime.getElapsedTime().asSeconds())));
		}
	}
	heartSprite.setPosition(sf::Vector2f(mainPlayer->playerRect.getPosition().x - 650, mainPlayer->playerRect.getPosition().y - 400));
	initalHeartText.setPosition(sf::Vector2f(heartSprite.getPosition().x+45,heartSprite.getPosition().y+65));
	initalHeartText.setString(std::to_string(mainPlayer->lives));
	levelTimeHUD.setPosition(sf::Vector2f(mainPlayer->playerRect.getPosition().x + 500, mainPlayer->playerRect.getPosition().y - 350));
	initalGemHUD.setPosition(mainPlayer->playerRect.getPosition().x-50, mainPlayer->playerRect.getPosition().y - 375);
	initalGemHUD.setScale(sf::Vector2f(0.75, 0.75));
	initalGemText.setString(std::to_string(mainPlayer->coinCount));
	initalGemText.setPosition(sf::Vector2f(initalGemHUD.getPosition().x + 40, initalGemHUD.getPosition().y + 30));
}

void level::onComplete(player *mainPlayer) {
	levelFinished = true;
	mainPlayer->movingControlProtected = false;
	mainPlayer->movingLeftPermitted = false;
	mainPlayer->movingRightPermitted = false;
}