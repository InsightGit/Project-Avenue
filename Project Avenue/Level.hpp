#pragma once
#ifndef __LEVEL_HPP_INCLUDED__
#define __LEVEL_HPP_INCLUDED__
#include <string>
#include <fstream>
#include <vector>
#include <SFML\Graphics.hpp>
#include "Player.hpp"

class level {
    public:
	std::ifstream worldFile;
	std::string levelId;
	bool drawBackground = false;
	sf::Font initalFont;
	sf::Text initalText;
	sf::Text initalHeartText;
	sf::Texture heart;
	sf::Sprite heartSprite;
	sf::View levelView = sf::View(sf::FloatRect(0,0,1366,768));
	int subscene = 0;

	std::vector<std::string> worldFileLines;

	level(const std::string worldFileLocation,sf::Font defaultFont, player *player1);

	int spawn();
	void updateView(player mainPlayer);
};
#endif