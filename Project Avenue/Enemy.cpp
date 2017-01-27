#include "Enemy.hpp"
#include <thread>

enemy::enemy(int id, sf::Vector2f position) {
	enemyPosition = position;
	switch (id) {
		case 1:
			attackStrength=1;
			lives = 1;
			sightRadius = 500;
			speed = 10;
			enemySize = 50;
			enemySpeed = 100;
			enemyCircle = sf::CircleShape(enemySize);
			enemyCircle.setFillColor(sf::Color::Red);
			enemyCircle.setPosition(enemyPosition);
			circleInit = true;
		//default:
			//throw std::runtime_error("Unknown enemy id");
		case 2:
			attackStrength = 1;
			enemySize = 50;
			sf::Texture texture;
			if (!texture.loadFromFile("Spikes.png")) {
				throw std::runtime_error("Could not load Spikes.png");
			}
			enemySprite.setTexture(texture);
			enemySprite.setPosition(enemyPosition);
	}
}
enemy::enemy(){}

void enemy::attack(player *playerToAttack) {
	if (id == 2) {
		return;
	}
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
	if (id == 2) {
		return 0;
	}
	lives -= livesToDeduct;
	if (lives <= 0) {
		enemyCircle.setPosition(sf::Vector2f(-1000000000, -1000000000));
	}
	return 0;
}

void enemy::update(bool collided, sf::Vector2f collisionPoint) {
	/* if (currentPlayer->playerRect.getPosition().x - enemyCircle.getPosition().x <= sightRadius) {
		if (!currentPlayer->playerRect.getPosition().x - enemyCircle.getPosition().x > -15) {
			attack(currentPlayer);
		}
	} */
	if (id == 2) {
		return;
	}
	if (collided && collisionPoint.x!=pastCollison.x && !limitDirectionChanges) {
		if (moving == 'l') {
			moving = 'r';
		}
		else if (moving == 'r') {
			moving = 'l';
		}
	}
	pastCollison = collisionPoint;
}