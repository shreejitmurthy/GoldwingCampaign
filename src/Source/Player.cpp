#include "Player.hpp"

#include "raymath.h"

float get_look_angle(Vector3 position, Vector3 direction) {
    float dx = position.x - direction.x;
    float dz  = position.z - direction.z;
    return atan2f(dx, dz);
}

void key_bindings(Controls& controls) {
    controls.forward.addKey(KEY_W);
    controls.back.addKey(KEY_S);
    controls.left.addKey(KEY_A);
    controls.right.addKey(KEY_D);
}

float LerpAngle(float a, float b, float t) {
    float difference = std::fmod(b - a, 360.0f * DEG2RAD);
    if (difference > 180.0f * DEG2RAD) {
        difference -= 360.0f * DEG2RAD;
    } else if (difference < -180.0f * DEG2RAD) {
        difference += 360.0f * DEG2RAD;
    }
    return a + difference * t;
}


Player::Player(AssetManager am) : Actor(0, 0, 0) {
    controls.init(key_bindings);
    // This is kinda wack, but it work
    am.LoadModelAsset("player", "../res/models/guy.obj");
    model = am.GetModel("player");
    bBox = GetModelBoundingBox(model);
    height = 3.f;
    angle = 0.f;
    move_base_angle = 0;
}

Player::~Player() {
    UnloadModel(model);
}

void Player::update(float dt) {
    
}

void Player::drawHealth(Camera3D camera) const {
    Vector2 playerHealthPos = GetWorldToScreen((Vector3){position.x, position.y + 2.f, position.z}, camera);
    DrawText("? / ?", (int)playerHealthPos.x - MeasureText("? / ?", 20)/2, (int)playerHealthPos.y, 20, BLACK);
}

void Player::draw() const {
    DrawModelEx(model, position, {0, 1, 0}, angle*RAD2DEG, {1, 1, 1}, WHITE);
    DrawBoundingBox(bBox, LIME);
}

void Player::updateLookDirection(Vector3 direction) {
    float base_angle = get_look_angle(position, direction);

    bool forward = actionKeyDown({controls.forward});
    bool back    = actionKeyDown({controls.back});
    bool left    = actionKeyDown({controls.left});
    bool right   = actionKeyDown({controls.right});

    float targetAngle = angle;

    if (directionDependantTurn) {
        if (forward && !back && !left && !right) {
            targetAngle = base_angle;
        } else if (back && !forward && !left && !right) {
            targetAngle = base_angle + 180 * DEG2RAD;
        } else if (left && !right && !forward && !back) {
            targetAngle = base_angle + 90 * DEG2RAD;
        } else if (right && !left && !forward && !back) {
            targetAngle = base_angle - 90 * DEG2RAD;
        } 
        // Diagonal directions
        else if (forward && left) {
            targetAngle = base_angle + 45 * DEG2RAD;
        } else if (forward && right) {
            targetAngle = base_angle - 45 * DEG2RAD;
        } else if (back && left) {
            targetAngle = base_angle + 135 * DEG2RAD;
        } else if (back && right) {
            targetAngle = base_angle - 135 * DEG2RAD;
        }
    } else {
        if (forward || back) {
            isTurnLocked = false;

            if (forward && !back) {
                if (left && !right) {
                    targetAngle = base_angle + 45 * DEG2RAD;
                } else if (right && !left) {
                    targetAngle = base_angle - 45 * DEG2RAD;
                } else {
                    targetAngle = base_angle;
                }
            } else if (back && !forward) {
                if (left && !right) {
                    targetAngle = base_angle + 135 * DEG2RAD;
                } else if (right && !left) {
                    targetAngle = base_angle - 135 * DEG2RAD;
                } else {
                    targetAngle = base_angle + 180 * DEG2RAD;
                }
            }
        }
        else if (left || right) {
            if (!isTurnLocked) {
                if (left && !right) {
                    lockedTurnAngle = base_angle + 90 * DEG2RAD;
                } else if (right && !left) {
                    lockedTurnAngle = base_angle - 90 * DEG2RAD;
                }
                isTurnLocked = true;
            }
            targetAngle = lockedTurnAngle;
        }
        else {
            isTurnLocked = false;
        }

    }

    angle = LerpAngle(angle, targetAngle, 0.5);
}
