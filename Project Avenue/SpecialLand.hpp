#pragma once
#include <SFML\Graphics.hpp>

class specialLand {
	public:
	sf::Texture specialTexture;
	sf::Sprite specialSprite;
	
	specialLand();
	specialLand(sf::Texture specialLandTexture);
};