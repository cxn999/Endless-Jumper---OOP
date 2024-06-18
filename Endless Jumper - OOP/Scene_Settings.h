#pragma once

#include "Scene.h"
#include <map>
#include <memory>
#include <deque>

#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Scene_Settings : public Scene {
protected:
	sf::Text m_titleText;
	std::vector<sf::Text> m_texts;
	std::vector<std::string> m_menuStrings;
	std::vector <std::string> m_levelPaths;
	sf::Text m_menuText;
	int m_selectedMenuIndex = 0;

	// New UI elements
	sf::RectangleShape m_volumeSlider;
	sf::Text m_volumeText;
	sf::Text m_musicToggleText;
	sf::Text m_controlSchemeText;

	// State variables
	float m_volume = 50.0f; // Initial volume level
	bool m_musicOn = true; // Initial music state
	bool m_useWASD = true; // Initial control scheme

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);
	sf::Color getVolumeColor(float volume);
	void updateVolumeSlider();

public:
	Scene_Settings(GameEngine* gameEngine = nullptr);
	void sRender();
};
