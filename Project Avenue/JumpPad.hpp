#pragma once
#include "SpecialLand.hpp"

class jumpPad : specialLand {
public:
	int jumpHeight;
	int id; 
	
	jumpPad();
	jumpPad(int id,sf::Vector2f jumpPadPosition);
	jumpPad(int id, sf::Vector2f jumpPadPosition,const std::string customJumpPadTextureLocation);
};