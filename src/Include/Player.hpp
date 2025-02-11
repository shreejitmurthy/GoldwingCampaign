#pragma once

#include "raylib.h"

#include "Actor.hpp"

#include "Controls.hpp"

class Player : public Actor {
public:
    float height;
    float angle;
    float move_base_angle;
    bool isTurnLocked;
    float lockedTurnAngle;
    bool directionDependantTurn;

    Player(AssetManager am);
    ~Player();

    void update(float dt) override;
    void drawHealth(Camera3D camera) const override;
    void draw() const override;

    void updateLookDirection(Vector3 direction);

private:
    Model model;
    BoundingBox bBox;
    Controls controls;
};