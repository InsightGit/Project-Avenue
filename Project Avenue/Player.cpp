#include "Player.hpp"
#include "Weapon.hpp"
#include "Enemy.hpp"
#include "Level.hpp"
#include <iostream>

player::player(sf::Vector2f position) {
	//position = playerPosition;
	walkSpeed = 15;
	jumpDistance = 200;
	playerRect.setPosition(position);
	playerRect.setFillColor(sf::Color::Black);
}

player::player(sf::Vector2f position, level *mainLevel) {
	currentLevel = mainLevel;
	playerRect.setPosition(position);
	playerRect.setFillColor(sf::Color::Black);
}

player::player(){
	std::cout << "default\n";
}

void player::possessWeapon(weapon *weaponToPossess) {
	weaponToPossess->owner = this;
	weaponToPossess->weaponRect.setPosition(sf::Vector2f(playerRect.getPosition().x + 100, playerRect.getPosition().y));
	weaponToPossess->ownerType = "Player";
}

void player::attacked(int livesToDeduct) {
	lives -= livesToDeduct;
	if (lives <= 0) {
		//put game over when done
	}
}

void player::jump(float *timer, int *playerIntersectCount) {
	if (jumpByJumpPad) {
		if (jumpState == 0) {
			//playerRect.setPosition(sf::Vector2f(playerRect.getPosition().x, playerRect.getPosition().y-jumpSpeed));
			if (positionBeforeJump.y - playerRect.getPosition().y >= jumpDistance) {
				jumpState = 1;
			}
			else {
				playerRect.move(0, jumpSpeed / -1);
			}
		}
		if (jumpState == 1 && *timer <= 0.f) {
			//if (positionBeforeJump.y == playerRect.getPosition().y) {
			if (*playerIntersectCount>0) {
				jumpState = 2;
			}
			else {
				playerRect.move(0, jumpSpeed);
			}
		}
	}
}