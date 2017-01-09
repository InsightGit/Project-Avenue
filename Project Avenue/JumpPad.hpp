#pragma once
#include "SpecialLand.hpp"
#include "Player.hpp"

class jumpPad : specialLand {
public:
	int jumpHeight;
	int id; 
	
	jumpPad();
	jumpPad(int id,sf::Vector2f jumpPadPosition);
	jumpPad(int id, sf::Vector2f jumpPadPosition,const std::string customJumpPadTextureLocation);

	void onCollison(player *ColiddingPlayer);
};