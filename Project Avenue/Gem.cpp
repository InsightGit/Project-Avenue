#include "Gem.hpp"
#include <stdexcept>
#include "Player.hpp"
#include "Level.hpp"

gem::gem(int id, sf::Vector2f position) {
	if (id == 1) {
		gemValue = 1;
		if (!gemTexture.loadFromFile("gem.png")) {
			throw std::runtime_error("Could not open gem texture for id 1 (gem.png)");
		}
		gemSprite.setTexture(gemTexture);
		gemSprite.setPosition(position);
	}
	else if (id == 2) {
		gemValue = -1;
		if (!gemTexture.loadFromFile("FinishGem.png")) {
			throw std::runtime_error("Could not open gem texture for id 2 (FinishGem.png)");
		}
		gemSprite.setTexture(gemTexture);
		gemSprite.setPosition(position);
	}
}

gem::gem(int id, const std::string *customTextureLocation, sf::Vector2f position) {
	if (id == 1) {
		gemValue = 1;
		if (!gemTexture.loadFromFile(*customTextureLocation) != 0) {
			throw std::runtime_error("Could not open gem texture for id 1. CUSTOM Texture used.");
		}
		gemSprite.setTexture(gemTexture);
		gemSprite.setPosition(position);
	}else if (id == 2) {
		gemValue = -1;
		if (!gemTexture.loadFromFile(*customTextureLocation) != 0) {
			throw std::runtime_error("Could not open gem texture for id 1. CUSTOM Texture used.");
		}
		gemSprite.setTexture(gemTexture);
		gemSprite.setPosition(position);
	}
}

void gem::onCollect(player *playerToAddTo, sf::SoundBuffer *soundBufferToPlay) {
	if (!protectGem) {
		if (id == 2 && gemValue == -1) {
			playerToAddTo->currentLevel->onComplete(playerToAddTo);
		}
		else {
			playerToAddTo->coinCount += gemValue;
		}
	}
	coinCollectSound.setBuffer(*soundBufferToPlay);
	gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
	protectGem = true;
	coinCollectSound.play();
}

void gem::onCollect(player *playerToAddTo) {
	if (!protectGem) {
		if (id == 2 && gemValue == -1) {
			playerToAddTo->currentLevel->onComplete(playerToAddTo);
		}
		else {
			playerToAddTo->coinCount += gemValue;
		}
	}
	gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
	protectGem = true;
}