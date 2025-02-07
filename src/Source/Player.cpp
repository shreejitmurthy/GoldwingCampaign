#include "Player.hpp"

float get_look_angle(Vector3 position, Vector3 direction) {
    float dx = position.x - direction.x;
    float dz  = position.z - direction.z;
    return atan2f(dx, dz);
}

void key_bindings(controls_t *controls) {
    controls->forward = (action_t){{KEY_W}, 2, 0};
    controls->back    = (action_t){{KEY_S}, 2, 0};
    controls->left    = (action_t){{KEY_A}, 2, 0};
    controls->right   = (action_t){{KEY_D}, 2, 0};
}

Player::Player(AssetManager am) : Actor(0, 0, 0) {
    init_controls(&controls, key_bindings);
    // This system lowkey lame but it works. 
    am.LoadModelAsset("player", "../res/models/guy.obj");
    model = am.GetModel("player");
    bBox = GetModelBoundingBox(model);
    height = 3.f;
    angle = 0.f;
}

Player::~Player() {
    UnloadModel(model);
}

// TODO
void Player::update(float dt) {
    
}

void Player::drawHealth(Camera3D camera) const {
    Vector2 playerHealthPos = GetWorldToScreen((Vector3){position.x, position.y + 2.f, position.z}, camera);
    DrawText("? / ?", (int)playerHealthPos.x - MeasureText("? / ?", 20)/2, (int)playerHealthPos.y, 20, BLACK);
}

void Player::draw() const {
    // DrawModel(model, position, 1.0f, WHITE);
    DrawModelEx(model, position, {0, 1, 0}, angle*RAD2DEG, {1, 1, 1}, WHITE);
    DrawBoundingBox(bBox, LIME);
}

void Player::lookAt(Vector3 direction) {
    float base_angle = get_look_angle(position, direction);
    
    bool forward = action_key_down({controls.forward});
    bool back = action_key_down({controls.back});
    bool left = action_key_down({controls.left});
    bool right = action_key_down({controls.right});

    if (forward && !back && !left && !right) {
        angle = base_angle;
    } else if (back && !forward && !left && !right) {
        angle = base_angle + 180 * DEG2RAD;
    } else if (left && !right && !forward && !back) {
        angle = base_angle + 90 * DEG2RAD;
    } else if (right && !left && !forward && !back) {
        angle = base_angle - 90 * DEG2RAD;
    } 
    // Diagonal directions
    else if (forward && left) {
        angle = base_angle + 45 * DEG2RAD;
    } else if (forward && right) {
        angle = base_angle - 45 * DEG2RAD;
    } else if (back && left) {
        angle = base_angle + 135 * DEG2RAD;
    } else if (back && right) {
        angle = base_angle - 135 * DEG2RAD;
    }
}
