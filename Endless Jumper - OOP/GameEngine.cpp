#include "Scene.h"
#include "Scene_Menu.h"
#include "GameEngine.h"
#include "Scene_Play.h"

GameEngine::GameEngine(const std::string& path) {
	// Calling the init function
	srand(time(NULL));
	init(path);
}

void GameEngine::init(const std::string& path) {
	//std::ifstream fin(path);
	// TO DO: READ CONFIG FILE
	
	m_assets.loadFromFile(path);

	// Create a window with the specified resolution
	m_window.create(sf::VideoMode(1280, 720), "ENDLESS JUMPER");
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