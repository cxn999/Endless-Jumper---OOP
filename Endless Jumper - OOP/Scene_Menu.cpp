#pragma warning(disable : 4996)

#include "Scene_Menu.h"
#include "Scene_Shop.h"
#include "Scene_Settings.h"
#include "Scene_Play.h"
#include "GameEngine.h"

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init() {
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::Enter, "ENTER");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::Up, "UP");
	registerAction(sf::Keyboard::Down, "DOWN");

	m_backgroundIndex = rand()%8;

	// Set the sf::window in a more convenient variable
	auto& m_window = m_game->window();
	// Extract the font from the assets
	auto& f = m_game->getAssets().getFont("RETROGAMING");
	// Calculate middle of the screen in X axis
	auto mx = m_window.getView().getCenter().x;
	// Set the titleText
	m_titleText = sf::Text(m_title, f, 80);
	// Set it's position and it's color


	sf::FloatRect textBounds = m_titleText.getLocalBounds();
	m_titleText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
	m_titleText.setPosition(m_window.getSize().x / 2.0f, 100);

	m_titleText.setColor(sf::Color::Black);
	m_titleText.setOutlineColor(sf::Color::White);
	m_titleText.setOutlineThickness(1.f);
	// Constant for the fontSize of the levels
	int levels_fontSize = 50;

	// Add levels text to the vector
	m_texts.push_back(sf::Text("Play", f, levels_fontSize));
	m_texts.push_back(sf::Text("Shop", f, levels_fontSize));
	m_texts.push_back(sf::Text("Settings", f, levels_fontSize));

	std::string helpText("UP: W   DOWN: S   ENTER: ENTER   BACK: ESC");
	m_texts.push_back(sf::Text(helpText, f, 30));
	m_texts[3].setPosition(20, m_window.getSize().y - 50);
	m_texts[3].setColor(sf::Color::Black);
	m_texts[3].setOutlineColor(sf::Color::White);
	m_texts[3].setOutlineThickness(1.f);

	for (int i = 0; i < 3; i++) {
		m_texts[i].setPosition(mx - m_texts[i].getGlobalBounds().width / 2.f, 250 + 100 * i);
		m_texts[i].setOutlineColor(sf::Color::White);
		m_texts[i].setOutlineThickness(1.f);
	}

	// Music to add
	// auto & menuMusic = m_game->getAssets().getMusic("menuMusic", PATH);
	// menuMusic.play() or whatever
}

void Scene_Menu::update() {
	m_entityManager.update();
	sRender();
}

void Scene_Menu::onEnd() {
	m_game->quit();
}

void Scene_Menu::sDoAction(const Action& action) {
	if (action.type() == "START") {
		auto& clickSound = m_game->getAssets().getSound("clickSound");
		auto& enterSound = m_game->getAssets().getSound("enterSound");
		if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "ENTER") {
			enterSound.setVolume(m_game->getVolume());
			if (m_selectedMenuIndex == 0) {
				m_game->changeScene("PLAY", std::make_shared<Scene_Play>(m_game), true);
			}
			else if (m_selectedMenuIndex == 1) {
				enterSound.play();
				m_game->changeScene("SHOP", std::make_shared<Scene_Shop>(m_game), true);
			}
			else if (m_selectedMenuIndex == 2) {
				enterSound.play();
				m_game->changeScene("SETTINGS", std::make_shared<Scene_Settings>(m_game), true);
			}
		}
		else if (action.name() == "DOWN") { m_selectedMenuIndex = (m_selectedMenuIndex + 1) % 3; 
			clickSound.setVolume(m_game->getVolume());
			clickSound.play();
		}
		else if (action.name() == "UP") { m_selectedMenuIndex = (m_selectedMenuIndex + 2) % 3; 
			clickSound.setVolume(m_game->getVolume());
			clickSound.play();
		}
	}
}

void Scene_Menu::sRender() {
	// Store sf::window in a variable for more convenience
	auto& m_window = m_game->window();
	m_window.setView(m_window.getDefaultView());
	// Calculate middle of the screen in X axis
	auto mx = m_window.getSize().x / 2;
	// Clear the window with blue
	m_window.clear(sf::Color::Transparent);

	for (auto& bg : m_game->getAssets().getBackground(m_backgroundIndex).getLayers()) {
		bg.setColor(sf::Color(255, 255, 255));
		bg.setPosition(m_game->window().getView().getCenter().x/2.f, m_game->window().getView().getCenter().y / 2.f);
		m_game->window().draw(bg);
	}


	// Iterate through the text vector and set their respective color and position
	for (int i = 0; i < 3; i++) {
		if (i != m_selectedMenuIndex) {
			m_texts[i].setColor(sf::Color::Black);
		}
		else {
			m_texts[i].setColor(sf::Color::White);
		}
		// Draw the levels text
		m_window.draw(m_texts[i]);
	}

	// Draw the title
	m_window.draw(m_titleText);
	m_window.draw(m_texts[3]);

	// Display the window
	m_window.display();
}
