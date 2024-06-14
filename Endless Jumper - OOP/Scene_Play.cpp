#include "Scene_Play.h"
#include "Scene_Menu.h"
#include "Physics.h"
#include "Assets.h"
#include "GameEngine.h"
#include "Components.h"
#include "Action.h"
#include <fstream>

#include <iostream>

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath) 
	: Scene(gameEngine)
	, m_levelPath(levelPath) 
{
	init(m_levelPath);
}

void Scene_Play::init(const std::string& levelPath) {
	registerAction(sf::Keyboard::P, "PAUSE");
	registerAction(sf::Keyboard::Escape, "QUIT");
	registerAction(sf::Keyboard::T, "TOGGLE_TEXTURE"); // Toggle drawing textures
	registerAction(sf::Keyboard::C, "TOGGLE_COLLISION"); // Toggle drawing collision boxes
	registerAction(sf::Keyboard::G, "TOGGLE_GRID");
	registerAction(sf::Keyboard::W, "UP"); //POSSIBLE DOUBLE JUMP LATER
	registerAction(sf::Keyboard::A, "LEFT");
	registerAction(sf::Keyboard::D, "RIGHT");

	// TODO: REGISTER ALL OTHER GAMEPLAY ACTIONS

	m_gridText.setCharacterSize(12);
	// m_gridText.setFont(m_game->getAssets().getFont("NAMEFONT"))
	loadLevel(levelPath);
}

void Scene_Play::sDoAction(const Action& action) {
	if (action.type() == "START") {
		if (action.name() == "TOGGLE_TEXTURE") { m_drawTextures = !m_drawTextures; }
		else if (action.name() == "TOGGLE_COLLISION") { m_drawCollision = !m_drawCollision; }
		else if (action.name() == "TOGGLE_GRID") { m_drawGrid = !m_drawGrid; }
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
}

void Scene_Play::update() {
	m_entityManager.update();
	if (!m_paused) {
		sCollision();
		sMovement();
		//sLifespan();
		sAnimation();
	}
	sRender();
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity) {
	// Bullet should go in direction player is facing
}

void Scene_Play::spawnPlayer() {
	// sample code
	m_player = m_entityManager.addEntity("player");
	m_player->addComponent<CAnimation>(m_game->getAssets().getAnimation("playerFall"), false);
	m_player->getComponent<CAnimation>().animation.getSprite().setScale(2, 2);
	auto size = m_player->getComponent<CAnimation>().animation.getSprite().getGlobalBounds();
	m_player->addComponent<CBoundingBox>(Vec2(size.getSize().x, size.getSize().y));

	m_player->addComponent<CTransform>(Vec2(m_game->window().getSize().x / 2, m_game->window().getSize().y / 2));
	// Remember to change again.
	m_player->addComponent<CGravity>();
	m_player->addComponent<CState>();
}

void Scene_Play::loadLevel(const std::string& levelpath) {
	// reset the entity manager every time we load a level
	m_entityManager = EntityManager();

	std::ifstream file(levelpath);
	std::string identifier;

	if (!file.is_open()) {
		std::cerr << "Error opening file...\n";
		exit(EXIT_FAILURE);
	}

	while (file >> identifier) {
		std::string name;
		int x, y;;
		if (identifier == "tile") {
			file >> name >> x >> y;
			auto e = m_entityManager.addEntity(identifier);
			e->addComponent<CAnimation>(m_game->getAssets().getAnimation(name), false);
			e->getComponent<CAnimation>().animation.getSprite().setScale(2, 2);
			auto size = e->getComponent<CAnimation>().animation.getSprite().getGlobalBounds();
			e->addComponent<CBoundingBox>(Vec2(size.getSize().x,size.getSize().y));
			e->addComponent<CTransform>(Vec2(x*m_gridSize.x+m_gridSize.x/2, m_game->window().getSize().y-y*m_gridSize.y-m_gridSize.y / 2));
			auto pos = e->getComponent<CTransform>().pos;
			e->getComponent<CAnimation>().animation.getSprite().setPosition(pos.x, pos.y);
		}
	}

	spawnPlayer();
}

void Scene_Play::sRender() {
	auto & player_pos = m_player->getComponent<CTransform>().pos;
	auto& window = m_game->window();
	window.clear(sf::Color::Black);


	// Define parallax speeds for each background layer
	float parallaxSpeed1 = 0.8f; // Farthest background
	float parallaxSpeed2 = 0.7f;
	float parallaxSpeed3 = 0.6f;
	float parallaxSpeed4 = 0.5f; // Closest background
	float parallaxSpeed5 = 0.3f;
	float parallaxSpeed6 = 0.1f; // Closest background

	// Calculate parallax offsets based on player position
	float offset1 = player_pos.y * parallaxSpeed1;
	float offset2 = player_pos.y * parallaxSpeed2;
	float offset3 = player_pos.y * parallaxSpeed3;
	float offset4 = player_pos.y * parallaxSpeed4;
	float offset5 = player_pos.y * parallaxSpeed5;
	float offset6 = player_pos.y * parallaxSpeed6;

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

	sf::View view(sf::Vector2f(window.getSize().x/2, player_pos.y), sf::Vector2f(1024, 720.f));
	view.setViewport(sf::FloatRect(0.1f, 0, 0.8, 1));
	window.setView(view);
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
	if (m_drawGrid) {
		for (int i = 1; i<12; i++) {
			sf::RectangleShape linex(sf::Vector2f(m_game->window().getSize().x, 1));
			linex.setFillColor(sf::Color::White);
			linex.setPosition(0, 64*i);
			window.draw(linex);
		}
		for (int i = 1; i < 20; i++) {
			sf::RectangleShape liney(sf::Vector2f(m_game->window().getSize().y, 1));
			liney.rotate(90);
			liney.setFillColor(sf::Color::White);
			liney.setPosition(64*i, 0);
			window.draw(liney);
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
			}
		}
		// check if player hits the tile from the bottom
		if (0 < overlap.x && -m_gridSize.y < overlap.y && dy < 0) {
			if (0 <= overlap.y && prevOverlap.y <= 0) {
				player.pos.y += overlap.y;
				player.velocity.y = 0;
			}
		}
		// check player and tile side collide
		float dx = tile.pos.x - player.pos.x;
		if (0 < overlap.y && -m_gridSize.x < overlap.x) {
			if (0 <= overlap.x && prevOverlap.x <= 0) {
				if (dx > 0) {
					// tile is right of player
					player.pos.x -= overlap.x;
				}
				else {
					// tile is left of player
					player.pos.x += overlap.x;
				}
			}
		}
	}
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity) {
	return Vec2(0, 0);
}

void Scene_Play::sMovement() {
	auto& input = m_player->getComponent<CInput>();
	auto& player_pos = m_player->getComponent<CTransform>().pos;
	auto& player = m_player->getComponent<CTransform>();
	auto& player_velocity = m_player->getComponent<CTransform>().velocity;
	player_velocity.x = 0;


	if (input.left) {
		player_velocity.x = -5;
		m_player->getComponent<CState>().state = "run";
	}
	if (input.right) {
		player_velocity.x = 5;
		m_player->getComponent<CState>().state = "run";
 	}
	if (input.down) {
		player_velocity.y = 5;
	}
	if (input.up) {
		player_velocity.y = -50;
		m_player->getComponent<CState>().state = "run";
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
}

void Scene_Play::onEnd() {
	m_game->changeScene("MENU", std::make_shared<Scene_Menu>(m_game), true);
}

