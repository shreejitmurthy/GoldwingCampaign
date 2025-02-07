#include "Player.hpp"

Player::Player(AssetManager am) : Actor(0, 0, 0) {
        // model = LoadModel("../res/models/guy.obj")
        // This system lowkey lame but it works. 
        am.LoadModelAsset("player", "../res/models/guy.obj");
        model = am.GetModel("player");
        bBox = GetModelBoundingBox(model);
        height = 3.f;
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
    DrawModel(model, position, 1.0f, GRAY);
    DrawBoundingBox(bBox, LIME);
}
