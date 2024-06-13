#pragma once

#include "Scene.h"
#include <map>
#include <memory>
#include <deque>

#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Scene_Menu : public Scene {
protected:
	std::string m_title = "PLATFORMS GAME";
	sf::Text m_titleText;
	std::vector<sf::Text> m_texts;
	std::vector<std::string> m_menuStrings;
	std::vector <std::string> m_levelPaths;
	sf::Text m_menuText;
	int m_selectedMenuIndex = 0;

	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	Scene_Menu(GameEngine* gameEngine = nullptr);
	void sRender();
};