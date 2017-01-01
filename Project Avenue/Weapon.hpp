#pragma once
#ifndef __WEAPON_HPP_INCLUDED__
#define __WEAPON_HPP_INCLUDED__
#include <SFML\Graphics.hpp>
#include <stdexcept>
#include <vector>
#include <string>
//#include "Player.hpp"
//#include "Enemy.hpp"
class player;
class enemy;
class weapon {
	public:
		std::string name;
		sf::RectangleShape weaponRect;
		int id;
		int strength;
		int bulletSpeed = 1;
		int delaySecs = 1;
		player *owner;
		enemy *enemyOwner;
		std::string ownerType = "None";

		std::vector<sf::CircleShape> bullet;

		weapon();
		weapon(int id);

		void update();
		void attack(enemy enemyToAttack);
		void attack(player playerToAttack);
		bool isAttacking();
};
#endif