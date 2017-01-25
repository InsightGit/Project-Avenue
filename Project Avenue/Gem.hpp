#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>


class player;
class gem {
public:
	int gemId;
	int gemValue = 0;
	sf::Sound coinCollectSound;
	sf::Texture gemTexture;
	sf::Sprite gemSprite;
	bool protectGem = false;
	bool isContained = false;
	bool collected = false;

	gem();
	gem(int id);
	gem(int id, sf::Vector2f position);
	gem(int id, const std::string *customTextureLocation, sf::Vector2f position);

	void onCollect(player *playerToAddTo, sf::SoundBuffer *soundBufferToPlay);
	void onCollect(player *playerToAddTo);
	void update();
};