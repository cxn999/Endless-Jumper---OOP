#pragma once
#include <vector>		/// include vector library
#include <memory>		/// include shared pointers
#include <map>			/// include map
#include "Entity.h"		/// include the entity header file

/// typedef for convenience
typedef std::vector<std::shared_ptr<Entity>> EntityVec;
typedef std::map<std::string, EntityVec> EntityMap;

/// Class that handles all the entities in the game (creates them, deletes them, modifies them, etc.)
class EntityManager {
	EntityVec m_entities;				/// entities vector
	EntityVec m_toAdd;					/// a vector that contains the entities that will be added in the next frame
	EntityMap m_entityMap;				/// a map for all the entities respective to their tag
	size_t m_totalEntities = 0;			/// quantity of entities in the game

	void removeDeadEntities(EntityVec& vec);	/// remove dead entities, it is private because that way only EntityManager can do it 

public:
	EntityManager() {};	/// default constructor
	void init();		/// initializes the entity manager
	void update();		/// adds or deletes the entities at the start of every frame

	std::shared_ptr<Entity> addEntity(const std::string& tag); /// adds a reference to a new entity into the entity vector
	EntityVec& getEntities();								   /// returns all entities in the game
	EntityVec& getEntities(const std::string& tag);			   /// returns all entities according to their tag
};