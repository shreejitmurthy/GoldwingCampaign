#pragma once

#include "raylib.h"

#include "Actor.hpp"

#include "Controls.hpp"

class Player : public Actor {
public:
    float height;
    float angle;
    float move_base_angle;
    bool isTurning;
    float turningTargetAngle;
    bool isTurnLocked;
    float lockedTurnAngle;

    Player(AssetManager am);
    ~Player();

    void update(float dt) override;
    void drawHealth(Camera3D camera) const override;
    void draw() const override;

    void updateAngle(Vector3 direction);

private:
    Model model;
    BoundingBox bBox;
    controls_t controls;
};