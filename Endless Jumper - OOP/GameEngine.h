#pragma once

#include "Assets.h"		/// include assets class
#include <memory>		/// shared pointers library
#include <map>			/// include map library
#include <string>		
#include <iostream>

class Scene;			/// class declaration to avoid circular dependency

/// typedef for convenience
typedef std::map<std::string, std::shared_ptr<Scene>> SceneMap;

/// Game Engine class
class GameEngine {
	sf::RenderWindow m_window;		/// creates an instance of a window 
	Assets m_assets;				/// assets object
	std::string m_currentScene;		/// identifier for the current scene
	SceneMap m_sceneMap;			/// map for the scenes

	size_t m_coins;					/// variable for coins
	float m_volume;					/// variable for volume
	size_t m_highestScore;			/// variable for highest score
	bool m_music;					/// variable for music (on or off)
	bool m_wasd;					/// variable for controls (WASD or KEYS)

	bool m_running = true;			/// if the game is running or not, used for exiting the game

	/// Load the assets
	void init(const std::string& path);
	void update();						/// checks user input and updates the scene						

	void sUserInput();					/// registers all the input in the game and checks if they have a corresponding action on the scene
	std::shared_ptr<Scene> currentScene();	/// method that returns the actual scene

public:

	/// constructor that receives the path of the config and the assets
	GameEngine(const std::string& path, const std::string& path2);

	/// Change scene  
	void changeScene(const std::string &, std::shared_ptr<Scene> scene, bool endCurrentScene);

	/// Main loop of the game
	void run();
	/// quits the game
	void quit();
	
	Assets& getAssets();		/// returns a reference to the assets object
	sf::RenderWindow& window();	/// returns a reference to the window

	/// returns if the game is running or not
	bool isRunning();

	/// methods to get configurations
	size_t getCoins();
	float getVolume();
	size_t getHighestScore();
	bool getMusic();
	bool getWASD();

	/// methods to set configurations
	void setCoins(size_t coins);
	void setVolume(float volume);
	void setHighestScore(size_t highestScore);
	void setMusic(bool music);
	void setWASD(bool wasd);
};