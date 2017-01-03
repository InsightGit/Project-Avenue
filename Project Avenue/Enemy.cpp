#include "Enemy.hpp"
#include <thread>

enemy::enemy(int id, sf::Vector2f position) {
	enemyPosition = position;
	switch (id) {
		case 1:
			attackStrength=1;
			lives = 1;
			sightRadius = 15;
			speed = 10;
			enemySize = 50;
			enemyCircle = sf::CircleShape(enemySize);
			enemyCircle.setFillColor(sf::Color::Red);
		default:
			throw std::runtime_error("Unknown enemy id");
	}
	enemyCircle.setPosition(enemyPosition);
}
enemy::enemy(){}

void enemy::attack(player playerToAttack) {
	sf::Vector2f distance(enemyPosition.x- playerToAttack.playerRect.getPosition().x, 0);
	while (!enemyPosition.x - playerToAttack.playerRect.getPosition().x <= enemySize+10) {
		enemyCircle.move(sf::Vector2f(100, 0));
	}
	playerToAttack.attacked(attackStrength);
}

int enemy::attacked(int livesToDeduct) {
	lives -= livesToDeduct;
	if (lives <= 0) {
		enemyCircle.setPosition(sf::Vector2f(-1000000000, -1000000000));
	}
	return 0;
}

void enemy::update(player currentPlayer) {
	if (currentPlayer.playerRect.getPosition().x - enemyCircle.getPosition().x <= sightRadius) {
		if (!currentPlayer.playerRect.getPosition().x - enemyCircle.getPosition().x > -15) {
			std::thread attackingThread(attack,currentPlayer);
		}
	}
}