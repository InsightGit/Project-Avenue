#include "ImagineArena.hpp"
#include "Player.hpp"

imagine::arena::arena() {}

imagine::arena::arena(std::string id,player *otherPlayer) {
	arenaId = id;
	player2 = otherPlayer;
}

void imagine::arena::spawn(player *mainPlayer) {
	if (arenaId == "level1") {
		sf::RectangleShape landRect1 = sf::RectangleShape(sf::Vector2f(1000, 600));
		landRect1.setPosition(sf::Vector2f(-600, 700));
		landRect1.setFillColor(sf::Color::Green);
		landRects.push_back(landRect1);
	}
	player2->playerRect.setFillColor(sf::Color::Red);
	bool spawned = true;
}

void imagine::arena::updateView(player *mainPlayer) {
	arenaView.reset(sf::FloatRect(mainPlayer->playerRect.getPosition().x, mainPlayer->playerRect.getPosition().y, 1366, 768));
	arenaView.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));
	arenaView.setCenter(mainPlayer->playerRect.getPosition());
}