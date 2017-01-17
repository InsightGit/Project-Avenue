#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

namespace imagine {
	class waitRoom {
	    public:
		std::vector<sf::RectangleShape> landRects;
		sf::Text displayText;
		sf::Font defaultFont;
		int id;

		waitRoom(std::string displayTextMessage, sf::Font fontToUse, int id);
		virtual ~waitRoom();
	};
}