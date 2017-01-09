#include "JumpPad.hpp"
#include <stdexcept>

specialLand::specialLand(){} 

jumpPad::jumpPad(int id, sf::Vector2f jumpPadPosition) {
	if (id == 1) {
		jumpHeight = 200;
		if (specialTexture.loadFromFile("jumpPad.png")) {
			throw std::runtime_error("Could not load JumpPad default texture (jumpPad.png)");
		}
		specialSprite.setPosition(jumpPadPosition);
	}
}

jumpPad::jumpPad(int id, sf::Vector2f jumpPadPosition, const std::string customJumpPadTextureLocation) {
	if (id == 1) {
		jumpHeight = 200;
		if (specialTexture.loadFromFile(customJumpPadTextureLocation)) {
			throw std::runtime_error("Could not load JumpPad custom texture");
		}
		specialSprite.setPosition(jumpPadPosition);
	}
}

void jumpPad::onCollison(player *ColiddingPlayer) {
	ColiddingPlayer->playerRect.move(sf::Vector2f(0,jumpHeight));
	ColiddingPlayer->jumpByJumpPad = true;
}