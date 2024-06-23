#pragma once

#include <map>					// include map library
#include <string>				
#include <SFML/Graphics.hpp>	// include graphics library
#include <SFML/Audio.hpp>		// include audio library
#include "Animation.h"			// header file for animation
#include "Background.h"			// header file for background

// typedef the name of these variables for convenience
typedef std::map<std::string, sf::Texture> Textures;	
typedef std::map<std::string, Animation> AnimationsMap;
typedef std::map<std::string, sf::Sound> Sounds;
typedef std::map<std::string, sf::Music> Music;
typedef std::map<std::string, sf::Font> Fonts;
typedef std::map<int, Background> Backgrounds;

class Assets {
	// maps for the different types of assets
	AnimationsMap m_animations;
	Backgrounds m_backgrounds;
	Textures m_textures;
	Sounds m_sounds;
	Fonts m_fonts;
public:

	// methods to add different types of assets to their respective assets's maps
	void addTexture(const std::string& name, const std::string& path);
	void addSound(std::string& name, std::string& path);
	void addFont(const std::string& name, const std::string& path);
	void addAnimation(const std::string& name, const Animation & animation);
	void addBackground(const int name, const int index2, const sf::Texture&);
	void addMusic(); // Add corresponding parameters and definition in assets.cpp

	// method to get different types of assets to ther respective assets's maps
	sf::Texture & getTexture(const std::string & name);
	sf::Sound & getSound(std::string& name);
	sf::Font & getFont(const std::string& name);
	Animation & getAnimation(const std::string& name);
	Background& getBackground(const int name);
	void getMusic(); // Add corresponding parameters and definition in assets.cpp

	// method to retrieve all the assets of the game and store them in their respective maps
	void loadFromFile(const std::string& path);
};