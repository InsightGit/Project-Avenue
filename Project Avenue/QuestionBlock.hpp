#pragma once
#include "SpecialLand.hpp"
#include "Gem.hpp"

class questionBlock : public specialLand {
	public:
	gem *gemContained;
	sf::Vector2f pastGemPosition;
	sf::Texture usedTexture;
	bool isUsed = false;

	questionBlock(gem *gemToContain, sf::Vector2f questionBlockPosition);
	questionBlock(gem *gemToContain , const std::string fileName, const std::string usedFileName, const sf::Vector2f questionBlockPosition);

	void changeGem(gem *gemToContain);
	void onPlayerHit();
};