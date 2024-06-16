#include "Scene_Play.h"
#include "Scene_Menu.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include <fstream>
#include <cstdlib>
#include <time.h>
#include <iostream>

Scene_Play::Scene_Play(GameEngine* gameEngine) 
	: Scene(gameEngine)
{
	srand(time(NULL));
	init();
}

void Scene_Play::init() {
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE"); // Toggle drawing textures
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION"); // Toggle drawing collision boxes
	registerAction(sf::Keyboard::W, "UP"); //POSSIBLE DOUBLE JUMP LATER
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");

	loadLevel();

	auto& window = m_game->window();
	auto player_pos = m_player->getComponent<CTransform>().pos;

	m_view = sf::View(sf::Vector2f(window.getSize().x / 2, player_pos.y), sf::Vector2f(1024, 720.f));
	m_view.setViewport(sf::FloatRect(0.1f, 0, 0.8, 1));
	window.setView(m_view);
}

void Scene_Play::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "PAUSE") { setPaused(!m_paused); }
		else if (action.name() == "QUIT") { onEnd(); }
		if (action.name() == "RIGHT") {
			m_player->getComponent<CInput>().right = true;	
		}
		if (action.name() == "LEFT") {
			m_player->getComponent<CInput>().left = true;
		}
		if (action.name() == "UP") {
			m_player->getComponent<CInput>().up = true;
		}
		// ADD REMAINING ACTIONS
	}
	else if (action.type() == "END") {
		if (action.name() == "RIGHT") {
			m_player->getComponent<CInput>().right = false;
		}
		if (action.name() == "UP") {
			m_player->getComponent<CInput>().up = false;
		}
		if (action.name() == "LEFT") {
			m_player->getComponent<CInput>().left = false;
		}
	}

	m_score.setFont(m_game->getAssets().getFont("RETROGRAMING"));
	m_score.setFillColor(sf::Color::White);
	m_score.setCharacterSize(90);
	m_score.setPosition(500, 30);
}

void Scene_Play::update() {
	sRemoveDeadPlatforms();
	m_entityManager.update();
	if (!m_paused) {
		sCollision();
		sMovement();
		sPlatformGeneration();
		sAnimation();
	}
	sRender();
	m_currentFrame++;
}


void Scene_Play::spawnPlayer() {
	m_player = m_entityManager.addEntity("player");
	m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("playerFall"), false);
	m_player->getComponent<CAnimation>().animation.getSprite().setScale(2, 2);
	auto size = m_player->getComponent<CAnimation>().animation.getSprite().getGlobalBounds();
	m_player->addComponent<CBoundingBox>(Vec2(size.getSize().x, size.getSize().y));
	m_player->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, -20));
	m_player->addComponent<CGravity>();
	m_player->addComponent<CState>();
}

void Scene_Play::loadLevel() {
	// reset the entity manager every time we load a level
	m_entityManager = EntityManager();

	size_t initialPlatformCount = 70;
	
	spawnPlayer();

	auto& window = m_game->window();

	auto x_spawn_min = window.getView().getViewport().getPosition().x * window.getSize().x;
	int win_width = window.getView().getSize().x*0.8;

	float y_pos = m_player->getComponent<CTransform>().pos.y - 50.0f;
	for (int i = 0; i < initialPlatformCount; ++i) {
			auto tile = m_entityManager.addEntity("tile");
			y_pos -= 100.0f;  // Adjust spacing between tiles
			tile->addComponent<CAnimation>(m_game->getAssets().getAnimation("grass01"), false);
			tile->getComponent<CAnimation>().animation.getSprite().setScale(0.15, 0.15);
			auto size = tile->getComponent<CAnimation>().animation.getSprite().getGlobalBounds();
			tile->addComponent<CBoundingBox>(Vec2(size.getSize().x, size.getSize().y));

			if (i == 0) {
				tile->addComponent<CTransform>(m_player->getComponent<CTransform>().pos+Vec2(0,60));
			}
			else {
				int size_x = tile->getComponent<CBoundingBox>().size.x;
				auto x_pos = (rand() % (win_width - size_x*2)) + x_spawn_min + size_x*2;
				tile->addComponent<CTransform>(Vec2(x_pos, y_pos));
			}
			auto pos = tile->getComponent<CTransform>().pos;
			tile->getComponent<CAnimation>().animation.getSprite().setPosition(pos.x, pos.y);
	}
}

void Scene_Play::sRender() {
	auto & player_pos = m_player->getComponent<CTransform>().pos;
	auto& window = m_game->window();
	window.clear(sf::Color::Black);


	window.setView(m_view);

	auto & view_center = m_view.getCenter();


	// Define parallax speeds for each background layer
	float parallaxSpeed1 = 0.8f; // Farthest background
	float parallaxSpeed2 = 0.7f;
	float parallaxSpeed3 = 0.6f;
	float parallaxSpeed4 = 0.5f; // Closest background
	float parallaxSpeed5 = 0.3f;
	float parallaxSpeed6 = 0.1f; // Closest background`

	// Calculate parallax offsets based on player position
	float offset1 = view_center.y * parallaxSpeed1;
	float offset2 = view_center.y * parallaxSpeed2;
	float offset3 = view_center.y * parallaxSpeed3;
	float offset4 = view_center.y * parallaxSpeed4;
	float offset5 = view_center.y * parallaxSpeed5;
	float offset6 = view_center.y * parallaxSpeed6;

	// Adjust background positions with parallax effect
	auto bg1 = m_game->getAssets().getAnimation("background1").getSprite();
	auto bg2 = m_game->getAssets().getAnimation("background2").getSprite();
	auto bg3 = m_game->getAssets().getAnimation("background3").getSprite();
	auto bg4 = m_game->getAssets().getAnimation("background4").getSprite();
	auto bg5 = m_game->getAssets().getAnimation("background5").getSprite();
	auto bg6 = m_game->getAssets().getAnimation("background6").getSprite();

	bg1.setPosition(bg1.getPosition().x, offset1- bg1.getGlobalBounds().height/3.5f);
	bg2.setPosition(bg2.getPosition().x, offset2 - bg2.getGlobalBounds().height / 3.5f);
	bg3.setPosition(bg3.getPosition().x, offset3 - bg3.getGlobalBounds().height / 3.5f);
	bg4.setPosition(bg4.getPosition().x, offset4 - bg4.getGlobalBounds().height / 3.5f);
	bg5.setPosition(bg5.getPosition().x, offset5 - bg5.getGlobalBounds().height / 3.5f);
	bg6.setPosition(bg6.getPosition().x, offset6 - bg6.getGlobalBounds().height / 3.5f);

	// Draw background layers
	window.draw(bg1);
	window.draw(bg2);
	window.draw(bg3);
	window.draw(bg4);
	window.draw(bg5);
	window.draw(bg6);
	
	m_score.setString(std::to_string(abs(player_pos.y)));
	window.draw(m_score);
	
	

	if (m_drawTextures) {
		for (auto e : m_entityManager.getEntities()) {
			window.draw(e->getComponent<CAnimation>().animation.getSprite());
		}
	}

	if (m_drawCollision) {
		for (auto e : m_entityManager.getEntities()) {
			auto size_x = e->getComponent<CBoundingBox>().size.x;
			auto size_y = e->getComponent<CBoundingBox>().size.y;
			sf::RectangleShape BoundingBox(sf::Vector2f(size_x, size_y));
			BoundingBox.setOrigin(e->getComponent<CBoundingBox>().halfSize.x, e->getComponent<CBoundingBox>().halfSize.y);
			BoundingBox.setPosition(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y);
			BoundingBox.setOutlineColor(sf::Color::Blue);
			BoundingBox.setFillColor(sf::Color::Transparent);
			BoundingBox.setOutlineThickness(1);
			window.draw(BoundingBox);
		}
	}
	window.display();
}

void Scene_Play::sAnimation() {
	auto& player = m_player->getComponent<CTransform>();
	auto player_state = m_player->getComponent<CState>().state;
	auto& animation = m_player->getComponent<CAnimation>().animation;

	if (player_state == "jump") {
		if (animation.getName() != "playerJump") {
			animation = m_game->getAssets().getAnimation("playerJump");
		}
	}
	else if (player_state == "fall") {
		if (animation.getName() != "playerFall") {
			animation = m_game->getAssets().getAnimation("playerFall");
		}
	}

	animation.getSprite().setScale(2, 2);

	if (player.pos.x < player.prevPos.x) {
		if (animation.getSprite().getScale().x != -2) {
			animation.getSprite().scale(-1, 1);
		}
	}
	else if (player.pos.x > player.prevPos.x) {
		if (animation.getSprite().getScale().x != 2) {
			animation.getSprite().scale(-1, 1);
		}
	}
	
	m_player->getComponent<CAnimation>().animation.getSprite().setPosition(player.pos.x, player.pos.y);
	m_player->getComponent<CAnimation>().animation.update();
}

// OLD COLLISION SYSTEM

void Scene_Play::sCollision() {
	auto& player = m_player->getComponent<CTransform>();
	for (auto& e : m_entityManager.getEntities("tile")) {
		if (player.pos.y > player.prevPos.y) {
			auto& tile = e->getComponent<CTransform>();
			Vec2 overlap = GetOverlap(m_player, e);
			Vec2 prevOverlap = GetPreviousOverlap(m_player, e);

			float dy = tile.pos.y - player.pos.y;

			if (0 < overlap.x && -m_gridSize.y < overlap.x && dy > 0) {
				if (0 <= overlap.y && prevOverlap.y <= 0) {
					// stand on tile
					m_player->getComponent<CInput>().canJump = true;
					m_player->getComponent<CGravity>().gravity = 0;
					player.velocity.y = -20;
					// collision resolution
					player.pos.y -= overlap.y;
					m_move = true;
					m_targetViewPosition = Vec2(m_view.getCenter().x, tile.pos.y - 500);
				}
			}
		}
	}
}


sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
	return start + t * (end - start);
}

void Scene_Play::sMovement() {
	auto& input = m_player->getComponent<CInput>();
	auto& player_pos = m_player->getComponent<CTransform>().pos;
	auto& player = m_player->getComponent<CTransform>();
	auto& player_velocity = m_player->getComponent<CTransform>().velocity;
	player_velocity.x = 0;

	if (m_move) {
		// Calculate the new position using interpolation
		float t = 0.05f;  // Adjust t for the desired speed (0 < t < 1)
		sf::Vector2f currentViewPosition = m_view.getCenter();
		sf::Vector2f newViewPosition = lerp(currentViewPosition, sf::Vector2f(m_targetViewPosition.x, m_targetViewPosition.y), t);

		// Update the view's position
		m_view.setCenter(newViewPosition);

		// Check if the camera is close enough to the target position
		if (std::abs(newViewPosition.y - m_targetViewPosition.y) < 1.0f) {
			m_view.setCenter(sf::Vector2f(m_targetViewPosition.x, m_targetViewPosition.y));
			m_move = false;
		}
	}

	if (input.left) {
		player_velocity.x = -5;
		m_player->getComponent<CState>().state = "run";
	}
	if (input.right) {
		player_velocity.x = 5;
		m_player->getComponent<CState>().state = "run";
 	}
	if (input.up) {
		player_velocity.y = -50;
		m_player->getComponent<CState>().state = "jump";
	}
	if (player_pos.y > player.prevPos.y) {
		m_player->getComponent<CState>().state = "fall";
	}
	if (player_pos.y < player.prevPos.y) {
		m_player->getComponent<CState>().state = "jump";
	}

	m_player->getComponent<CTransform>().prevPos = player_pos;


	player_velocity.y += m_player->getComponent<CGravity>().gravity;
	player_pos += player_velocity;

	if (player_velocity.y > 20) {
		player_velocity.y = 20;
    }
	m_player->getComponent<CGravity>().gravity = 0.4;

	if (player.pos == player.prevPos) {
		m_player->getComponent<CState>().state = "idle";
	}

	auto y_score = m_game->window().getSize().y;

	m_score.setPosition(200, y_score + 20);
}

void Scene_Play::onEnd() {
	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game), true);
}

void Scene_Play::sPlatformGeneration() {
	auto & window = m_game->window();
	float highestPlatformY = m_entityManager.getEntities("tile").back()->getComponent<CTransform>().pos.y;

	auto& player_pos = m_player->getComponent<CTransform>().pos;

	auto x_spawn_min = window.getView().getViewport().getPosition().x*window.getSize().x;
	int win_width = window.getView().getSize().x;

	// Generate new platforms above the highest one if the player is nearing the top
	if (abs(player_pos.y) > abs(highestPlatformY)-300) {
		auto tile = m_entityManager.addEntity("tile");
		tile->addComponent<CAnimation>(m_game->getAssets().getAnimation("grass01"), false);
		tile->getComponent<CAnimation>().animation.getSprite().setScale(0.15, 0.15);
		auto size = tile->getComponent<CAnimation>().animation.getSprite().getGlobalBounds();
		tile->addComponent<CBoundingBox>(Vec2(size.getSize().x, size.getSize().y));
		int size_x = tile->getComponent<CBoundingBox>().size.x;
		auto pos_x = (rand() % (win_width - size_x*2)) + x_spawn_min + size_x;
		tile->addComponent<CTransform>(Vec2(pos_x, highestPlatformY - 100));
		auto pos = tile->getComponent<CTransform>().pos;
		tile->getComponent<CAnimation>().animation.getSprite().setPosition(pos.x, pos.y);
	}
}

void Scene_Play::sRemoveDeadPlatforms() {
	auto& view_center = m_view.getCenter();

	for (auto& tile : m_entityManager.getEntities("tile")) {
		auto& tile_pos = tile->getComponent<CTransform>().pos;
		if (abs(tile_pos.y)+400 < abs(view_center.y)) {
			tile->destroy();
			std::cout << m_entityManager.getEntities("tile").size() << std::endl;
		}
	}
}