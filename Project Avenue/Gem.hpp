#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Audio.hpp>


class player;
class gem {
public:
	int id;
	int gemValue = 0;
	sf::Sound coinCollectSound;
	sf::Texture gemTexture;
	sf::Sprite gemSprite;

	gem();
	gem(int id, sf::Vector2f position);
	gem(int id, const std::string *customTextureLocation, sf::Vector2f position);

	void onCollect(player *playerToAddTo, sf::SoundBuffer *soundBufferToPlay);
	void onCollect(player *playerToAddTo);
};