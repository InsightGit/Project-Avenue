#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Player.hpp"

namespace imagine {
	class waitRoom {
	    public:
		std::vector<sf::RectangleShape> landRects;
		std::vector<sf::Sprite> landSprites;
		std::vector<sf::Texture> landTextures;
		sf::Sprite readyLight;
		sf::Text displayText;
		sf::Font defaultFont;
		sf::View waitRoomView = sf::View(sf::FloatRect(0, 76800, 1366, 768));
		std::string id;
		bool spawned = false;

		waitRoom(std::string displayTextMessage, sf::Font fontToUse, std::string waitRoomId);
		waitRoom();
		//waitRoom();
		//virtual ~waitRoom();

		void spawn(player *mainPlayer);
		void updateView(player *mainPlayer);
	};
}