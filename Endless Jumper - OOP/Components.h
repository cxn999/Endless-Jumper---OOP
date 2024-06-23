#pragma once

#include "Animation.h"
#include "Assets.h"
#include "Vec2.h"
#include <string>

/// base class for a component
class Component {
public:
	bool has = false;	/// it defines if the component exists or not
};

/// class for modifying everything that its related to transformations and translations (movement for example)
class CTransform : public Component {
public:
	Vec2 pos = { 0.0, 0.0 };		/// vector for position
	Vec2 prevPos = { 0.0, 0.0 };	/// vector for previous position
	Vec2 velocity = { 0.0, 0.0 };	/// vector for velocity		

	CTransform() {}					/// default constructor
	CTransform(const Vec2 & p) : pos(p) {}	/// constructor that set position only (for tiles)
	CTransform(const Vec2& p, const Vec2& v) : pos(p), velocity(v) {}	///constructor that sets position and velocity
};

/// class for input of the player
class CInput : public Component {
public:
	bool up = false;
	bool right = false;
	bool left = false;
	bool canJump = true;
};

/// class that defines the hitbox of entities
class CBoundingBox : public Component {
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox() = default;
	CBoundingBox(const Vec2 & s) : size(s), halfSize(s.x/2, s.y/2) {}
};

/// class that defines the animation of an entity
class CAnimation : public Component {
public:
	Animation animation;
	bool repeat = false;
	CAnimation() {}
	CAnimation(const Animation & animation, bool r) : animation(animation), repeat(r) {}
};

/// class to define gravity for certain entities
class CGravity : public Component {
public:
	float gravity = 0;
	CGravity() {}
	CGravity(float g) : gravity(g) {}
};

/// class that defines a string for the state of the player, if it is jumping, moving, falling, etc.
class CState : public Component {
public:
	std::string state = "idle";
	CState() {}
	CState(std::string s) : state(s) {}
};

/// defines if an entity can kill the player
class CKill : public Component {
	
};

/// defines if an entity moves (logs in this case)
class CMove : public Component {

};