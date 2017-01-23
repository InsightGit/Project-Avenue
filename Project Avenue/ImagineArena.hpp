#pragma once
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

class player;
namespace imagine {
	class arena {
	public:
		std::string arenaId;
		std::vector<sf::RectangleShape> landRects;
		std::vector<sf::Sprite> landSprites;
		std::vector<sf::Texture> landTextures;
		sf::View arenaView = sf::View(sf::FloatRect(0, 76800, 1366, 768));
		player *player2;
		bool spawned = false;

		arena(std::string id,player *otherPlayer);
		arena();

		void spawn(player *mainPlayer);
		void updateView(player *mainPlayer);
	};
}