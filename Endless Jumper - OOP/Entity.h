#pragma once

#include "Components.h"		// include the components class
#include <string>
#include <tuple>			// include tuple library

// typedef tuple of all the components in the game
typedef std::tuple <
	CState,
	CGravity,
	CAnimation,
	CBoundingBox,
	CInput,
	CTransform,
	CKill,
	CMove
	> ComponentTuple;

// defines what an entity is
class Entity { 
	ComponentTuple m_components;	// an entity has a tuple of the components
	std::string m_tag = "default";	// tag associated to the entity (like an enemy or tile)
	bool m_active = true;			// defines whether the entity is alive or not
	size_t m_id = 0;				// an id number for each entity			

	// a private constructor for the entity, its private in order to avoid creating an entity 
	// outside the EntityManager.
	Entity(const size_t& id, const std::string& tag) : m_id(id), m_tag(tag) {}

	// make EntityManager class friend of the Entity class to use its constructor
	friend class EntityManager;

public:

	size_t id();				// returns the id of the entity
	bool isActive();			// returns whether the entity is active or not
	const std::string& tag();	// returns the tag of the entity
	void destroy();				// destroys the entity


	template <typename T, typename... TArgs>
	T & addComponent(TArgs&&... mArgs);

	// template method to determine if the entity has an specific component or not
	template <class T>
	bool hasComponent();

	// template method to get an specific component of an entity
	template <typename T>
	T & getComponent();
	template <typename T>
	const T& getComponent() const;

	// template method to remove an specicic component of an entity
	template <class T>
	void removeComponent();
};

template <typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... mArgs)
{
	auto& component = getComponent<T>();
	component = T(std::forward<TArgs>(mArgs)...);
	component.has = true;
	return component;
}


template <typename T>
T& Entity::getComponent() {
	return std::get<T>(m_components);
}

template <typename T>
const T& Entity::getComponent() const {
	return std::get<T>(m_components);
}

template <class T>
bool Entity::hasComponent() {
	return getComponent<T>().has;
}

template <class T>
void Entity::removeComponent() {
	getComponent<T>() = T();
}