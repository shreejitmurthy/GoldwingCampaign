#pragma once

#include <iostream>
#include "raylib.h"
#include "raymath.h"
#include "rcamera.h"

#include "AssetManager.hpp"
#include "Player.hpp"

enum class ScreenState {
    MainMenu,
    Gameplay
};

/* Helper Functions */
void DrawFontTrue(Font font, const char* text, Vector2 centerPosition, float fontSize, Color color);
void DrawTextTrue(const char* text, int x, int y, int fontSize, Color color);
void UpdateCamGoldwing(Camera3D* camera, int mode, float sensitivity, float zoomSensitivity, float smoothing);

class Game {
public:
    Game(int width, int height);
    void run();
private:
    void update();
    void draw();

    int screenWidth;
    int screenHeight;

    Player* player;
    Camera3D camera;

    Camera3D skyCam;

    AssetManager am;

    ScreenState currentScreen;

    Rectangle playRec;
};
