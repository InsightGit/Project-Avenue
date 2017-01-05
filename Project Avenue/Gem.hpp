#pragma once
#include <SFML\Graphics.hpp>


class player;
class gem {
public:
	int id;
	int gemValue = 0;
	sf::Texture gemTexture;
	sf::Sprite gemSprite;

	gem();
	gem(int id, sf::Vector2f position);
	gem(int id, std::string *customTextureLocation, sf::Vector2f position);

	void onCollect(player *playerToAddTo);
};