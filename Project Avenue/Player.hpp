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
	int walkSpeed = 10;
	int jumpSpeed = 20;
	int levelIntersectCount;
	int jumpState = 0;
	int jumpDistance = 100;
	sf::Vector2f positionBeforeJump;

	//sf::Vector2f playerPosition;
	sf::RectangleShape playerRect = sf::RectangleShape(sf::Vector2f(20,100));

	player(sf::Vector2f position);
	player();

	void possessWeapon(weapon weaponToPossess);
	void attacked(int livesToDeduct);
	void jump();
};
#endif