#pragma once

#include <memory>
#include "Vec2.h"
#include "Entity.h"

// calculates if two rectangles collide between them and returns by how many pixels they are colliding
Vec2 GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);

// calculates if the previouc position of a rectangle collides with the position of another rectangle and returns how many pixels
Vec2 GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b);