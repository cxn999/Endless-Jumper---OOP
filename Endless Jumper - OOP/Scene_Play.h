#pragma once
#include "Scene.h"
#include <vector>
#include <SFML/Graphics.hpp>

class Scene_Play : public Scene {
protected:
	sf::Text m_scoreText;
	size_t m_score;
	sf::View m_view;
	size_t m_currentBackground = 0;
	size_t m_pastBackground;
	size_t m_currentFrame = 0;
	int m_alpha = 255;
	bool m_drawTextures = true;
	bool m_drawCollision = false;
	bool m_move = false;
	bool m_transition = false;
	bool m_end = false;
	Vec2 m_gridSize = { 64,64 };
	Vec2 m_targetViewPosition;
	size_t m_platformSpacing = 100;

	std::shared_ptr<Entity> m_player;
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