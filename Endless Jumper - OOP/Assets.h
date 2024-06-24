#pragma once

#include <map>					/// include map library
#include <string>				
#include <SFML/Graphics.hpp>	/// include graphics library
#include <SFML/Audio.hpp>		/// include audio library
#include "Animation.h"			/// header file for animation
#include "Background.h"			/// header file for background

/// typedef the name of these variables for convenience
typedef std::map<std::string, sf::Texture> Textures;	
typedef std::map<std::string, Animation> AnimationsMap;
typedef std::map<std::string, sf::SoundBuffer> SoundBuffers;
typedef std::map<std::string, sf::Sound> Sounds;
typedef std::map<std::string, sf::Music*> Musics;
typedef std::map<std::string, sf::Font> Fonts;
typedef std::map<int, Background> Backgrounds;

/// <summary>
/// Class that stores every asset in the game (fonts, backgrounds, textures, sounds, animations, etc.)
/// </summary>
class Assets {
	/// maps for the different types of assets
	AnimationsMap m_animations;
	Backgrounds m_backgrounds;
	Textures m_textures;
	SoundBuffers m_soundBuffers;
	Fonts m_fonts;
	Musics m_musics;
	Sounds m_sounds;

public:
	//destructor
	~Assets();

	/// methods to add different types of assets to their respective assets's maps
	void addTexture(const std::string& name, const std::string& path);
	void addSoundBuffer(const std::string& name, const std::string& path);
	void addFont(const std::string& name, const std::string& path);
	void addAnimation(const std::string& name, const Animation & animation);
	void addBackground(const int name, const int index2, const sf::Texture&);
	void addMusic(const std::string& name, const std::string& path);

	/// method to get different types of assets to ther respective assets's maps
	sf::Texture & getTexture(const std::string & name);
	sf::SoundBuffer & getSoundBuffer(const std::string& name);
	sf::Sound& getSound(const std::string& name);
	sf::Font & getFont(const std::string& name);
	Animation & getAnimation(const std::string& name);
	Background& getBackground(const int name);
	sf::Music& getMusic(const std::string& name);

	/// method to retrieve all the assets of the game and store them in their respective maps
	void loadFromFile(const std::string& path);
};