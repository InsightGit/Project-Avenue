#include "QuestionBlock.hpp"
#include <stdexcept>

specialLand::specialLand(){}

questionBlock::questionBlock(gem *gemToContain, sf::Vector2f gemPosition) {
	gemContained = gemToContain;
	pastGemPosition = gemToContain->gemSprite.getPosition();
	gemContained->isContained = true;
	if (!specialTexture.loadFromFile("gemTexture.png")) {
		throw std::runtime_error("Could not open gem default texture. (gemTexture.png) ");
	}
	specialSprite.setTexture(specialTexture);
	gemContained->gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
}
questionBlock::questionBlock(gem *gemToContain, sf::Vector2f gemPosition, const std::string fileName) {
	gemContained = gemToContain;
	if (!specialTexture.loadFromFile(fileName)) {
		throw std::runtime_error("Could not open gem custom file texture");
	}
	specialSprite.setTexture(specialTexture);
	specialSprite.setPosition(gemPosition);
}
void questionBlock::onPlayerHit() {
	gemContained->gemSprite.setPosition(0,specialSprite.getPosition().y-gemContained->gemSprite.getGlobalBounds().height);
}
void questionBlock::changeGem(gem *gemToContain) {
	gemContained->isContained = false;
	gemContained->gemSprite.setPosition(pastGemPosition);
	gemContained = gemToContain;
	gemContained->isContained = true;
	gemContained->gemSprite.setPosition(pastGemPosition);
	gemContained->gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
}