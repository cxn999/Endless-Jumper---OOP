#pragma once
#include "Scene.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Scene_Play : public Scene {
protected:
	sf::Text m_gridText;
	std::string m_levelPath;
	size_t m_currentFrame = 0;
	size_t m_lastPlatformRender = 0;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_drawGrid = false;
	Vec2 m_gridSize = { 32,32 };

	std::shared_ptr<Entity> m_player;
	// player config>!?!?!?!?!?!?
public:
	Scene_Play(GameEngine* gameEngine, const std::string& levelPath);

	// Check which is public or private smh
	void init(const std::string & path);
	void update();

	void onEnd();

	// Systems
	void sPlatformGeneration();
	void sAnimation();
	void sMovement();
	void sEnemySpawner();
	void sCollision();
	void sRender();
	void sDoAction(const Action& a);
	void sDebug();

	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity> entity);

	// LOAD FROM FILE EACH BLOCK POSITION ETC
	void loadLevel(const std::string & levelpath);

	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

};