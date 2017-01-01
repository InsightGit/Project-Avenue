#include "Weapon.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

weapon::weapon(){}

weapon::weapon(int id) {
		if(id==1){
			name = "Sword of Black";
			strength = 1;
			weaponRect = sf::RectangleShape(sf::Vector2f(15,30));
			weaponRect.setFillColor(sf::Color::Color(220, 135, 46, 1));
		}
		else {
			throw std::runtime_error("Unknown weapon id");
		}
}

void weapon::update() {
	if (ownerType == "Player") {
		weaponRect.setPosition(sf::Vector2f(owner->playerRect.getPosition().x + 100, owner->playerRect.getPosition().y));
	}
	else if (ownerType == "Enemy") {
		weaponRect.setPosition(sf::Vector2f(enemyOwner->enemyPosition.x + enemyOwner->enemySize, enemyOwner->enemyPosition.y));
	}
}

void weapon::attack(enemy enemyToAttack) {
	sf::Vector2f distance(owner->playerRect.getPosition().x - enemyToAttack.enemyPosition.x, 0);
	while (!owner->playerRect.getPosition().x - enemyToAttack.enemyPosition.x <= 110) {
		owner->playerRect.move(sf::Vector2f(100, 0));
	}
	enemyToAttack.attacked(strength);
}

void weapon::attack(player playerToAttack) {
	sf::Vector2f distance(enemyOwner->enemyPosition.x - playerToAttack.playerRect.getPosition().x, 0);
	while (!enemyOwner->enemyPosition.x - playerToAttack.playerRect.getPosition().x <= enemyOwner->enemySize+10) {
		enemyOwner->enemyCircle.move(sf::Vector2f(100, 0));
	}
	playerToAttack.attacked(strength);
}