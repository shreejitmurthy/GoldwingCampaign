#pragma once

#include "raylib.h"

#include "AssetManager.hpp"

// Guys with HP and and a position
class Actor {
public:
    Vector3 position;

    Actor(float x = 0, float y = 0, float z = 0) : position{x, y, z} {}

    virtual ~Actor() {}

    // Pure virtual functions (must be implemented by derived classes)
    virtual void update(float dt) = 0;
    virtual void draw() const = 0;
    virtual void drawHealth(Camera3D camera) const = 0;
};