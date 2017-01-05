#pragma once
#ifndef __LEVEL_HPP_INCLUDED__
#define __LEVEL_HPP_INCLUDED__
#include <string>
#include <fstream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Gem.hpp"

//class gem;
class level {
    public:
	std::ifstream worldFile;
	std::string levelId;
	bool drawBackground = false;
	bool levelSpawned = false;
	sf::Font initalFont;
	sf::Text initalText;
	sf::Text initalHeartText;
	sf::Text levelTimeHUD;
	sf::Texture heart;
	sf::Sprite heartSprite;
	sf::View levelView = sf::View(sf::FloatRect(0, 76800,1366,768));
	sf::Clock levelTime;
	int subscene = 0;

	std::vector<std::string> worldFileLines;

	//std::vector<sf::RectangleShape> landRectShapes;
	std::vector<sf::RectangleShape> landRectShapes;
	int landRectShapesSize = -1;
	std::vector<enemy> levelEnemies;
	std::vector<gem> levelGems;

	level(const std::string worldFileLocation,sf::Font defaultFont, player *player1);

	int spawn();
	void update(player *mainPlayer);
	void updateView(player mainPlayer, sf::Vector2i worldCoords);
	void onComplete();
};
#endif