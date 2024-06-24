#pragma once

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Animation.h"
#include "Background.h"

typedef std::map<std::string, sf::Texture> Textures;
typedef std::map<std::string, Animation> AnimationsMap;
typedef std::map<std::string, sf::SoundBuffer> SoundBuffers;
typedef std::map<std::string, sf::Music*> Musics;
typedef std::map<std::string, sf::Font> Fonts;
typedef std::map<int, Background> Backgrounds;


class Assets {
	AnimationsMap m_animations;
	Backgrounds m_backgrounds;
	Textures m_textures;
	SoundBuffers m_soundBuffers;
	Fonts m_fonts;
	Musics m_musics;
public:
	~Assets();
	void addTexture(const std::string& name, const std::string& path);
	void addSoundBuffer(const std::string& name, const std::string& path);
	void addFont(const std::string& name, const std::string& path);
	void addAnimation(const std::string& name, const Animation & animation);
	void addBackground(const int name, const int index2, const sf::Texture&);
	void addMusic(const std::string& name, const std::string& path);

	sf::Texture & getTexture(const std::string & name);
	sf::SoundBuffer & getSoundBuffer(const std::string& name);
	sf::Font & getFont(const std::string& name);
	Animation & getAnimation(const std::string& name);
	Background& getBackground(const int name);
	sf::Music& getMusic(const std::string& name);

	void loadFromFile(const std::string& path);
};