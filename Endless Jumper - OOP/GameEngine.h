#pragma once

#include "Assets.h"
#include <memory>
#include <map>
#include <string>

#include <iostream>

class Scene;

typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

class GameEngine {
protected:
	sf::RenderWindow m_window;
	Assets m_assets;
	std::string m_currentScene;
	SceneMap m_sceneMap;
	size_t m_simulationSpeed = 1;

	size_t m_coins;
	size_t m_volume;
	size_t m_highestScore;
	bool m_music;
	bool m_wasd;

	bool m_running = true;

	// Should load the assets
	void init(const std::string& path);
	void update();

	void sUserInput();
	std::shared_ptr<Scene> currentScene();

public:
	GameEngine(const std::string& path, const std::string& path2);

	// Change scene  
	void changeScene(const std::string &, std::shared_ptr<Scene> scene, bool endCurrentScene);

	// Main loop of the game
	void run();
	// Maybe quit the game?
	void quit();
	
	Assets& getAssets();
	sf::RenderWindow& window();
	// const Assets & assets() const;
	bool isRunning();

	/*
		size_t m_coins;
	size_t m_volume;
	size_t m_HighestScore;
	bool m_music;
	bool m_wasd;
	*/

	size_t getCoins();
	size_t getVolume();
	size_t getHighestScore();
	bool getMusic();
	bool getWASD();

	void setCoins(size_t coins);
	void setVolume(size_t volume);
	void setHighestScore(size_t highestScore);
	void setMusic(bool music);
	void setWASD(bool wasd);
};