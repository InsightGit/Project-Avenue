#include "Player.hpp"
#include "Weapon.hpp"
#include "Enemy.hpp"
#include <iostream>

player::player(sf::Vector2f position) {
	//position = playerPosition;
	playerRect.setPosition(position);
	playerRect.setFillColor(sf::Color::Black);
	std::cout << "non-default\n";
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
	if(jumpState==0){
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
		if(*playerIntersectCount>0){
			jumpState = 2;
		}
		else {
			playerRect.move(0, jumpSpeed);
		}
	}
}