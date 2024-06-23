#pragma once

#include "Scene.h"	/// import scene header file
#include <map>		/// import map library
#include <memory>	/// import memory library
#include <SFML/Graphics.hpp>	/// import graphics library
#include "EntityManager.h"		/// import entity manager header file

/// derived class of the Scene base class to implement the menu Scene
class Scene_Menu : public Scene {
protected:
	std::string m_title = "SKYLIMIT";	/// string of the title of the game 
	sf::Text m_titleText;				/// text of the title of the game

	std::vector<sf::Text> m_texts;		/// vector of all the texts in the menu
	std::vector<std::string> m_menuStrings;	/// string of the menu
	sf::Text m_menuText;					/// text of the menu
	int m_selectedMenuIndex = 0;			/// is the selected menu index, it makes the index in which we are sitting highlighted
	size_t m_backgroundIndex;				/// index for the backgrounds in the menu

	/// definition of pure virtual method from the base class
	void init();						
	void update();
	void onEnd();
	void sDoAction(const Action& action);

public:
	/// constructor of the scene menu that receives a pointer to the game engine
	Scene_Menu(GameEngine* gameEngine = nullptr);
	/// pure virtual method for the rendering system
	void sRender();
};