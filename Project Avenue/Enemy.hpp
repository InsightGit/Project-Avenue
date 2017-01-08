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
	int enemySpeed;
	char moving = 'l';
	bool limitDirectionChanges = false;

	sf::Vector2f pastCollison;
	weapon *weaponPossesed;
	sf::Vector2f enemyPosition;
	sf::CircleShape enemyCircle;

	enemy(int id,sf::Vector2f position);
	enemy();

	void update(bool collided, sf::Vector2f collisionPoint);
	//bool isAttacking();
	int attacked(int livesToDeduct);

protected:

	void attack(player *playerToAttack);
};
#endif