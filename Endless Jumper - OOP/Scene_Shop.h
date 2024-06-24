#pragma once

#include "Scene.h"
#include <map>
#include <memory>
#include <deque>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "EntityManager.h"

class Scene_Shop : public Scene {
protected:
	void init();
	void update();
	void onEnd();
	void sDoAction(const Action& action);
	sf::Text textConfig(const std::string& stringForText, sf::Vector2f position, int size, sf::Font& font);
	sf::Color getDynamicColor(float time);
	

	sf::View backgroundView;
	sf::View textView;

	sf::Texture backgroundTexture; 
	sf::Texture idleTexture;
	sf::Texture venom;

	sf::Sprite background;

	sf::RectangleShape playerIdle[6];

	std::vector<sf::Vector2f> selectPosition;  

	
	std::vector<sf::Text> texts;

	int selectPositionIndex = 0;
	sf::RectangleShape select;

	bool skinPurchased[5] = { false, false, false, false, false };
	bool isEquipped[6] = { true, false, false, false, false, false };

	sf::Clock clock;
public:
	Scene_Shop(GameEngine* gameEngine = nullptr);
	void sRender();
};