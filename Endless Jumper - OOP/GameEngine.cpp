#include "Scene.h"
#include "Scene_Menu.h"
#include "GameEngine.h"
#include "Scene_Play.h"
#include <fstream>

GameEngine::GameEngine(const std::string& path, const std::string& path2) {
	// Calling the init function
	srand(time(NULL));

	std::ifstream file(path2);
	std::string identifier;

	if (!file.is_open()) {
		std::cerr << "Error opening file...\n";
		exit(EXIT_FAILURE);
	}

	while (file >> identifier) {
		size_t n;
		file >> n;
		if (identifier == "coins") {
			setCoins(n);
		}
		else if (identifier == "highestScore") {
			setHighestScore(n);
		}
		else if (identifier == "wasd") {
			setWASD(n);
		}
		else if (identifier == "volume") {
			setVolume(n);
		}
		else if (identifier == "music") {
			setMusic(n);
		}
	}

	init(path);
}

void GameEngine::init(const std::string& path) {

	
	m_assets.loadFromFile(path);

	// Create a window with the specified resolution
	m_window.create(sf::VideoMode(1280, 720), "SKYLIMIT", sf::Style::Close);
	// Set vertical sync for better performance
	m_window.setVerticalSyncEnabled(true);
	//m_window.setFramerateLimit(60);
	changeScene("MENU", std::make_shared<Scene_Menu>(this), false);
}

void GameEngine::update() {
	sUserInput();
	m_sceneMap[m_currentScene]->update();
}

void GameEngine::sUserInput() {
	sf::Event event;
	sf::View view = m_window.getDefaultView();
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed) {
			quit();
		}

		if (event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0.f, 0.f, event.size.width, event.size.height);
			m_window.setView(sf::View(visibleArea));
		}

		if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::X) {
				sf::Texture texture;
				texture.create(m_window.getSize().x, m_window.getSize().y);
				texture.update(m_window);
				if (texture.copyToImage().saveToFile("test.png")) {
					std::cout << "Screenshot saved to " << "test.png" << std::endl;
				}
			}
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
			// if the current scene does not have an action associated with this key, skip this event
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }

			// determine start or end action by whether it was key press or release
			const std::string actionType = (event.type == sf::Event::KeyPressed) ? "START" : "END";

			// look up the action and send the action to the scene
			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), actionType));
		}
	}
}

std::shared_ptr<Scene> GameEngine::currentScene() {
	return m_sceneMap[m_currentScene];
}

void GameEngine::run() {
	while (isRunning()) {
		update();
	}
}

// probably only this
void GameEngine::quit() {
	m_running = false;
}

Assets& GameEngine::getAssets() {
	return m_assets;
}

void GameEngine::changeScene(const std::string & sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene = false) {
	//if (endCurrentScene) {
	//	m_sceneMap[m_currentScene] = nullptr;
	//}
	if (sceneName == "PLAY") {
		stopMusic();
		switchToMusic("play");
	}
	else {
		if (m_currentMusic && getMusic() == true && m_currentMusic == m_assets.getMusic("play")) {
			stopMusic();
		}
		switchToMusic("menu");
	}
	m_currentScene = sceneName;
	m_sceneMap[sceneName] = scene;
}

sf::RenderWindow& GameEngine::window() {
	return m_window;
}

// const Assets & assets() const;
bool GameEngine::isRunning() {
	return m_running && m_window.isOpen();
}

size_t GameEngine::getCoins() {
	return m_coins;
}

float GameEngine::getVolume() {
	return m_volume;
}

size_t GameEngine::getHighestScore() {
	return m_highestScore;
}
bool GameEngine::getMusic() {
	return m_music;
}
bool GameEngine::getWASD() {
	return m_wasd;
}

void GameEngine::setCoins(size_t coins) {
	m_coins = coins;
}

void GameEngine::setVolume(float volume) {
	m_volume = volume;

	if (m_currentMusic) {
		m_currentMusic->setVolume(volume);
	}
	// Update volume for other sound effects as needed
}

void GameEngine::setHighestScore(size_t highestScore) {
	m_highestScore = highestScore;
}
void GameEngine::setMusic(bool music) {
	m_music = music;
}
void GameEngine::setWASD(bool wasd) {
	m_wasd = wasd;
}

void GameEngine::startMusic(const std::string& musicName) {
	if (getMusic()) {
		if (m_currentMusic) {
			m_currentMusic->stop();
		}
		m_currentMusic = m_assets.getMusic(musicName);
		if (m_currentMusic) {
			m_currentMusic->setVolume(m_volume);
			m_currentMusic->setLoop(true);
			m_currentMusic->play();
		}
		else {
			std::cerr << "Music not found: " << musicName << std::endl;
		}
	}
}

void GameEngine::stopMusic() {
	if (m_currentMusic) {
		m_currentMusic->stop();
		m_currentMusic = nullptr;
	}
}

void GameEngine::setMusicState(bool musicOn) {
	m_music = musicOn;
	if (m_music) {
		if (m_currentMusic) {
			m_currentMusic->play();
		}
	}
	else {
		if (m_currentMusic) {
			m_currentMusic->stop();
		}
	}
}

void GameEngine::switchToMusic(const std::string& musicName) {
	if (musicName == "menu") {
		m_currentMusic = getAssets().getMusic("menu");
	}
	else if (musicName == "play") {
		m_currentMusic = getAssets().getMusic("play");
	}



	sf::Music* newMusic = nullptr;

	if (musicName == "menu") {
		newMusic = getAssets().getMusic("menu");
	}
	else if (musicName == "play") {
		newMusic = getAssets().getMusic("play");
	}

	if (m_currentMusic != newMusic) {
		if (m_currentMusic) {
			m_currentMusic->stop();
		}
		m_currentMusic = newMusic;
		if (m_music && m_currentMusic) {
			m_currentMusic->setVolume(m_volume);
			m_currentMusic->play();
		}
	}
	else if (m_music && m_currentMusic && m_currentMusic->getStatus() != sf::Music::Playing) {
		m_currentMusic->setVolume(m_volume);
		m_currentMusic->play();
	}
}