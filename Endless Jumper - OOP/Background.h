#pragma once

#include <SFML/Graphics.hpp>	// include graphics library
#include "Vec2.h"				// include vec2 class
#include <vector>				// include vector library

class Background {
	std::vector<sf::Sprite> m_layers;	// vector that stores the sprites of the background
	int m_length = 0;					// the quantity of layers in a background

public:
	void addLayer(const sf::Texture &t);	// method to add the layers together to form the background
	Background();							// default constructor
	size_t getLength();						// method to get the quantity of layers
	std::vector<sf::Sprite> & getLayers();	// method to get the layers vectors of the background
};