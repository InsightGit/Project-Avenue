#pragma once
#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__
//#include "Weapon.hpp"
#include <SFML/Graphics.hpp>
class enemy;
class weapon;
class player {
public:
	int lives = 3;
	int level;
	sf::Vector2f playerPosition;
	sf::RectangleShape playerRect = sf::RectangleShape(sf::Vector2f(100,20));

	player();
	player(sf::Vector2f position);

	void possessWeapon(weapon weaponToPossess);
	void attacked(int livesToDeduct);
};
#endif