#pragma once
#include "SpecialLand.hpp"
#include "Player.hpp"

class jumpPad : public specialLand {
public:
	int jumpHeight;
	int id; 
	
	jumpPad();
	jumpPad(const int id,sf::Vector2f jumpPadPosition);
	jumpPad(const int id, sf::Vector2f jumpPadPosition,const std::string customJumpPadTextureLocation);

	void onCollison(player *ColiddingPlayer);
};