#include "JumpPad.hpp"
#include <stdexcept>

//specialLand::specialLand(){} 

jumpPad::jumpPad(int id, sf::Vector2f jumpPadPosition) {
	if (id == 1) {
		jumpHeight = 400;
		if (!specialTexture.loadFromFile("jumpPad.png")) {
			throw std::runtime_error("Could not load JumpPad default texture (jumpPad.png)");
		}
		specialSprite.setPosition(jumpPadPosition);
		specialSprite.setScale(0.75, 0.75);
	}
}

jumpPad::jumpPad(int id, sf::Vector2f jumpPadPosition, const std::string customJumpPadTextureLocation) {
	if (id == 1) {
		jumpHeight = 400;
		if (specialTexture.loadFromFile(customJumpPadTextureLocation)) {
			throw std::runtime_error("Could not load JumpPad custom texture");
		}
		specialSprite.setPosition(jumpPadPosition);
	}
}

void jumpPad::onCollison(player *ColiddingPlayer) {
	ColiddingPlayer->playerRect.move(sf::Vector2f(0,jumpHeight/-1));
	ColiddingPlayer->jumpByJumpPad = true;
}