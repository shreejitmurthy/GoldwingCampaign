#pragma once

#include "raylib.h"

#include "Actor.hpp"

#include "Controls.hpp"

class Player : public Actor {
public:
    float height;
    float angle;

    Player(AssetManager am);
    ~Player();

    void update(float dt) override;
    void drawHealth(Camera3D camera) const override;
    void draw() const override;

    void lookAt(Vector3 direction);

private:
    Model model;
    BoundingBox bBox;
    controls_t controls;
};