#pragma once
#include <string>

// SFML takes our keyboard input as code, each keycap has a code number. Action class
// takes every "action" and stores the name of the action, like "Move right" and it also stores if they are beggining or ending
class Action {
	std::string m_name;	// member that stores the action name
	std::string m_type;	// member that stores if the action is beggining or ending
public:
	Action();			// default constructor 
	Action(const std::string& name, const std::string& type);	// constructor that sets the name and type of the action

	const std::string& name() const;	// method to get the name of the action
	const std::string& type() const;	// method to get the type of the action
};