#include "QuestionBlock.hpp"
#include <stdexcept>

specialLand::specialLand(){}

questionBlock::questionBlock(gem *gemToContain, sf::Vector2f questionBlockPosition) {
	gemContained = gemToContain;
	pastGemPosition = gemToContain->gemSprite.getPosition();
	gemContained->isContained = true;
	if (!specialTexture.loadFromFile("QuestionBlock.png")) {
		throw std::runtime_error("Could not open questionBlock default texture. (QuestionBlock.png) ");
	}
	if (!usedTexture.loadFromFile("QuestionBlockOpen.png")) {
		throw std::runtime_error("Could not open questionBlock used default texture. (QuestionBlockOpen.png) ");
	}
	specialSprite.setTexture(specialTexture);
	specialSprite.setPosition(questionBlockPosition);
	gemContained->gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
}
questionBlock::questionBlock(gem *gemToContain, const std::string fileName, const std::string usedFileName, const sf::Vector2f questionBlockPosition) {
	gemContained = gemToContain;
	pastGemPosition = gemToContain->gemSprite.getPosition();
	gemContained->isContained = true;
	if (!specialTexture.loadFromFile(fileName)) {
		throw std::runtime_error("Could not open questionBlock custom file texture");
	}
	specialSprite.setTexture(specialTexture);
	specialSprite.setPosition(questionBlockPosition);

	if (!usedTexture.loadFromFile(usedFileName)) {
		throw std::runtime_error("Could not open questionBlock used custom file texture");
	}
	gemContained->gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
}
void questionBlock::onPlayerHit() {
	gemContained->gemSprite.setPosition(0,specialSprite.getPosition().y-gemContained->gemSprite.getGlobalBounds().height);
	specialSprite.setTexture(usedTexture);
	isUsed = true;
}
void questionBlock::changeGem(gem *gemToContain) {
	gemContained->isContained = false;
	gemContained->gemSprite.setPosition(pastGemPosition);
	gemContained = gemToContain;
	gemContained->isContained = true;
	gemContained->gemSprite.setPosition(pastGemPosition);
	gemContained->gemSprite.setPosition(sf::Vector2f(-1000000000, -1000000000));
}