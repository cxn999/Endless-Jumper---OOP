#pragma warning(disable : 4996)

#include "Scene_Settings.h"
#include "Scene_Menu.h"
#include "GameEngine.h"

Scene_Settings::Scene_Settings(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Settings::init() {
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::Enter, "ENTER");
	registerAction(sf::Keyboard::S, "DOWN");
	registerAction(sf::Keyboard::W, "UP");
	registerAction(sf::Keyboard::Up, "DOWN");
	registerAction(sf::Keyboard::Down, "UP");


	// Set the sf::window in a more convenient variable
	auto& m_window = m_game->window();
	// Extract the font from the assets
	auto& f = m_game->getAssets().getFont("RETROGAMING");
	// Calculate middle of the screen in X axis
	auto mx = m_window.getSize().x / 2;
	// Set the titleText
	// Set it's position and it's color
	m_titleText.setPosition(mx - m_titleText.getGlobalBounds().width / 2.f, 50);
	m_titleText.setColor(sf::Color::Black);

	// Constant for the fontSize of the levels
	int levels_fontSize = 50;

	// Add levels text to the vector
	m_texts.push_back(sf::Text("Element 1", f, levels_fontSize));
	m_texts.push_back(sf::Text("Element 2", f, levels_fontSize));
	m_texts.push_back(sf::Text("Element 3", f, levels_fontSize));

	std::string helpText("UP: W   DOWN: S   ENTER: ENTER   BACK: ESC");
	m_texts.push_back(sf::Text(helpText, f, 30));
	m_texts[3].setPosition(20, m_window.getSize().y - 50);
	m_texts[3].setColor(sf::Color::Black);

	for (int i = 0; i < 3; i++) {
		m_texts[i].setPosition(mx - m_texts[i].getGlobalBounds().width / 2.f, 250 + 100 * i);
	}
}

void Scene_Settings::update() {
	m_entityManager.update();
	sRender();
}

void Scene_Settings::onEnd() {
	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game), true);
}


void Scene_Settings::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		else if (action.name() == "ENTER") { std::cout << "ENTER PRESSED" << std::endl; }
		else if (action.name() == "DOWN") { m_selectedMenuIndex = (m_selectedMenuIndex + 1) % 3; }
		else if (action.name() == "UP") { m_selectedMenuIndex = (m_selectedMenuIndex + 2) % 3; }
	}
}

void Scene_Settings::sRender() {
	// Store sf::window in a variable for more convenience
	auto& m_window = m_game->window();
	// Calculate middle of the screen in X axis
	auto mx = m_window.getSize().x / 2;
	// Clear the window with blue
	m_window.clear(sf::Color::Magenta);

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
