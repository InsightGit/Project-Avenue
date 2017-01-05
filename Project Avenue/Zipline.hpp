#pragma once
#include "SpecialLand.hpp"

class player;
class zipland : specialLand {
	sf::Vector2f startCoords;
	sf::Vector2f endCoords;
	sf::RectangleShape lineToRideOn;

	void onRetrivePlayer(player *ridingPlayer)
};