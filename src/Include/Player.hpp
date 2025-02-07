#pragma once

#include "raylib.h"

#include "Actor.hpp"

class Player : public Actor {
public:
    float height;
    Player(AssetManager am);
    ~Player();

    void update(float dt) override;
    void drawHealth(Camera3D camera) const override;
    void draw() const override;

private:
    Model model;
    BoundingBox bBox;
};