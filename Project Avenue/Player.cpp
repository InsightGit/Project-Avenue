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

void player::possessWeapon(weapon weaponToPossess) {
	weaponToPossess.owner = this;
	weaponToPossess.weaponRect.setPosition(sf::Vector2f(playerPosition.x + 100, playerPosition.y));
	weaponToPossess.ownerType = "Player";
}

void player::attacked(int livesToDeduct) {
	lives -= livesToDeduct;
	if (lives <= 0) {
		//put game over when done
	}
}

