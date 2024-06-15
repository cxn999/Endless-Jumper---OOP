#pragma once
#include "Scene.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Scene_Play : public Scene {
protected:
	sf::Text m_score;
	size_t m_currentFrame = 0;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	Vec2 m_gridSize = { 32,32 };

	std::shared_ptr<Entity> m_player;
	// player config>!?!?!?!?!?!?
public:
	Scene_Play(GameEngine* gameEngine);

	// Check which is public or private smh
	void init();
	void update();

	void onEnd();

	// Systems
	void sRemoveDeadPlatforms();
	void sPlatformGeneration();
	void sAnimation();
	void sMovement();
	void sCollision();
	void sRender();
	void sDoAction(const Action& a);
	void spawnPlayer();
	void loadLevel();
};