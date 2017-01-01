#include "Player.hpp"
#include "Weapon.hpp"
#include "Enemy.hpp"

player::player(sf::Vector2f position) {
	position = playerPosition;
	playerRect.setPosition(playerPosition);
	playerRect.setFillColor(sf::Color::Black);
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

