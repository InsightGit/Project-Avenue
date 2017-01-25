#pragma once
#include <SFML\Graphics.hpp>

class specialLand {
	public:
	sf::Texture specialTexture;
	sf::Sprite specialSprite;

	//virtual position = 0;
	
	specialLand();
	specialLand(sf::Texture specialLandTexture);
};