#pragma once
#include "SpecialLand.hpp"
#include "Gem.hpp"

class questionBlock : specialLand {
	public:
	gem *gemContained;
	sf::Vector2f pastGemPosition;

	questionBlock(gem *gemToContain, sf::Vector2f gemPosition);
	questionBlock(gem *gemToContain, sf::Vector2f gemPosition,const std::string fileName);

	void changeGem(gem *gemToContain);
	void onPlayerHit();
};