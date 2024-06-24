#pragma once

#include <SFML/Graphics.hpp>	/// include graphics for the sprites
#include "Vec2.h"				/// defines vectors and things like distance or angles
#include <string>

/// stores all the information of animations in the game
class Animation {
	sf::Sprite m_sprite;			/// a rectangle that has an associated texture inside
	size_t m_frameCount = 1;		///	count the number of frames in a sprite (1 as default for platforms)
	size_t m_currentFrame = 0;		///	the current animation frame in which we are
	size_t m_speed = 0;				///	the speed at which the frames refresh
	Vec2 m_size = { 1,1 };			///	the size of the sprite
	std::string m_name = "none";	/// name of the animation

public:
	///constructor for things that move, like the player
	Animation(const std::string& name, const sf::Texture& t, size_t frameCount, size_t speed);
	///constructor for things that do not move, like a tile
	Animation(const std::string& name, const sf::Texture& t);
	Animation();

	void update();						/// passes to the next animation frame according to the speed
	std::string& getName();				/// method to get the name of the animation
	Vec2& getSize();					/// method to get the size of the animation
	sf::Sprite& getSprite();			/// method to get the sprite of the animation
};