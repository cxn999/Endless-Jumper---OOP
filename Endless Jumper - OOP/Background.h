#pragma once

#include <SFML/Graphics.hpp>
#include "Vec2.h"
#include <vector>

class Background {
	std::vector<sf::Sprite> m_layers;
	int m_length=0;

public:
	void addLayer(const sf::Texture &t);
	Background();
	size_t getLength();
	std::vector<sf::Sprite> & getLayers();
};