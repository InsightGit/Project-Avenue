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
			enemySpeed = 100;
			enemyCircle = sf::CircleShape(enemySize);
			enemyCircle.setFillColor(sf::Color::Red);
		//default:
			//throw std::runtime_error("Unknown enemy id");
	}
	enemyCircle.setPosition(enemyPosition);
}
enemy::enemy(){}

void enemy::attack(player *playerToAttack) {
	sf::Vector2f distance(enemyPosition.x- playerToAttack->playerRect.getPosition().x, 0);
	if (!enemyPosition.x - playerToAttack->playerRect.getPosition().x <= enemySize+10) {
		if (enemyPosition.x - playerToAttack->playerRect.getPosition().x > 0) {
			enemyCircle.move(sf::Vector2f(enemySpeed/-1, 0));
		}
		else if (!enemyPosition.x - playerToAttack->playerRect.getPosition().x < 0) {
			enemyCircle.move(sf::Vector2f(enemySpeed, 0));
		}
	}
	playerToAttack->attacked(attackStrength);
}

int enemy::attacked(int livesToDeduct) {
	lives -= livesToDeduct;
	if (lives <= 0) {
		enemyCircle.setPosition(sf::Vector2f(-1000000000, -1000000000));
	}
	return 0;
}

void enemy::update(bool collided) {
	/* if (currentPlayer->playerRect.getPosition().x - enemyCircle.getPosition().x <= sightRadius) {
		if (!currentPlayer->playerRect.getPosition().x - enemyCircle.getPosition().x > -15) {
			attack(currentPlayer);
		}
	} */
	if (collided) {
		if (moving == 'l') {
			moving = 'r';
		}
		else if (moving == 'r') {
			moving = 'l';
		}
	}

}