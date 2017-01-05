#pragma once
#ifndef __PLAYER_HPP_INCLUDED__
#define __PLAYER_HPP_INCLUDED__
#include <SFML/Graphics.hpp>
class level;
class enemy;
class weapon;
class player {
public:
	int lives = 3;
	int playerLevel;
	int walkSpeed = 10;
	int jumpSpeed = 20;
	int levelIntersectCount;
	int jumpState = 0;
	int jumpDistance = 150;
	int coinCount = 0;
	sf::Vector2f positionBeforeJump;
	level *currentLevel;

	//sf::Vector2f playerPosition;
	sf::RectangleShape playerRect = sf::RectangleShape(sf::Vector2f(20,100));

	player(sf::Vector2f position);
	player(sf::Vector2f position,level *currentLevel);
	player();

	void possessWeapon(weapon *weaponToPossess);
	void attacked(int livesToDeduct);
	void jump(float *timer, int *playerIntersectCount);
};
#endif