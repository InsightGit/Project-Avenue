#pragma once
#ifndef __ENEMY_HPP_INCLUDED__
#define __ENEMY_HPP_INCLUDED__
#include <SFML\Graphics.hpp>
#include "Player.hpp"
//#include "Weapon.hpp"
#include <string>
#include <stdexcept>


class enemy{
public:
	int id;
	int lives;
	int attackStrength;
	int sightRadius;
	int speed;
	int enemySize;
	weapon *weaponPossesed;
	sf::Vector2f enemyPosition;
	sf::CircleShape enemyCircle;

	enemy(int id,sf::Vector2f position);
	enemy();

	int update();
	bool isAttacking();
	int attacked(int livesToDeduct);

protected:

	int attack(player playerToAttack);
};
#endif