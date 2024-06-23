#pragma once

#include <map>				//include map library
#include <string>			//include string library
#include "Action.h"			//include action class
#include "EntityManager.h"	//include entity mangaer class

class GameEngine;	//circular dependency

// typedef for convenience
typedef std::map<int, std::string> ActionMap;

// base class that has all the basic functionalities for a scene
class Scene {
protected:
	GameEngine* m_game = nullptr;	// a reference to the game engine 
	EntityManager m_entityManager;	// an entity manager for the scene
	ActionMap m_actionMap;			// an action map for each scene
	size_t m_currentFrame;			// records the current frame
	bool m_paused = false;			// pause the game

	virtual void onEnd() = 0;		// pure virtual abstract method for quiting a scene

public:
	void setPaused(bool);			// pause the scene

	Scene();						//default constructor
	Scene(GameEngine* gameEngine);	//constructor that receives a pointer to the game engine

	// pure virtual method to update the frame depending on the scene
	virtual void update() = 0;
	// pure virtual method for the system of actions depending on the scene (Jump, move right, left, etc)
	virtual void sDoAction(const Action & action) = 0;
	// pure virtual method to render everything in the window in every frame=
	virtual void sRender() = 0;

	// virtual method that defines what an action does
	virtual void doAction(const Action& action);
	// method that registers every action in the scene
	void registerAction(int inputKey, const std::string & actionName);

	// method to return the current frame
	size_t currentFrame() const;

	// returns the associated actions to the scene
	const ActionMap& getActionMap() const;
};