#include "Game.hpp"

void DrawFontTrue(Font font, const char* text, Vector2 centerPosition, float fontSize, Color color) {
    Vector2 textSize   = MeasureTextEx(font, text, fontSize, 2);
    Vector2 drawPos    = Vector2Subtract(centerPosition, Vector2Scale(textSize, 0.5f));
    DrawTextEx(font, text, drawPos, fontSize, 4, color);
}

void DrawTextTrue(const char* text, int x, int y, int fontSize, Color color) {
    int textWidth = MeasureText(text, fontSize);
    DrawText(text, x - textWidth / 2, y + GetFontDefault().baseSize, fontSize, color);
}

void UpdateCamGoldwing(Camera3D* camera, int mode, float sensitivity, 
                       float zoomSensitivity, float smoothing) {
    Vector2 mouseDelta = GetMouseDelta();

    bool rotateAroundTarget = (mode == CAMERA_THIRD_PERSON);
    bool lockView = (mode == CAMERA_THIRD_PERSON);
    bool rotateUp = false;

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        CameraYaw(camera, -mouseDelta.x * sensitivity, rotateAroundTarget);
        CameraPitch(camera, -mouseDelta.y * sensitivity, lockView, rotateAroundTarget, rotateUp);
    }

    float zoomInput = -GetMouseWheelMove();

    float zoomChange = zoomInput * zoomSensitivity;

    Vector3 offset = Vector3Subtract(camera->position, camera->target);
    float currentDistance = Vector3Length(offset);

    float targetDistance = currentDistance + zoomChange;
    if (targetDistance < 1.f) targetDistance = 1.f;
    if (targetDistance > 5.f) targetDistance = 5.f;

    float newDistance = Lerp(currentDistance, targetDistance, smoothing);

    offset = Vector3Normalize(offset);
    offset = Vector3Scale(offset, newDistance);

    camera->position = Vector3Add(camera->target, offset);
}

Game::Game(int width, int height) : screenWidth(width), screenHeight(height) {
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "Goldwing");
    SetTargetFPS(60);

    player = new Player(am);

    const float cameraHeightOffset = player->height / 2.0f;
    camera.position   = { 0.0f, player->position.y + cameraHeightOffset, 4.0f };
    camera.target     = {player->position.x, player->position.y + cameraHeightOffset, player->position.z};
    camera.up         = { 0.0f, 1.0f, 0.0f };
    camera.fovy       = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    skyCam.position = (Vector3){ 0.0f, 10.0f, 0.0f };  // 5 units above the origin
    skyCam.target = (Vector3){ 0.0f, 0.0f, 0.0f };    // Looking at the origin
    skyCam.up = (Vector3){ 0.0f, 0.0f, -1.0f };       // "Up" is negative Z to align with top-down
    skyCam.fovy = 45.0f;                              // Field of view
    skyCam.projection = CAMERA_PERSPECTIVE;           // Perspective projection


    am.LoadFontAsset("menuFont", LoadFontEx("../res/fonts/MorrisRoman-Black.ttf", 24, 0, 0));

    currentScreen = ScreenState::MainMenu;

    playRec = (Rectangle){(float)(screenWidth / 2) - 125, (float)screenHeight - 200, 250, 50};
}

void Game::run()
{
    while (!WindowShouldClose()) {
        update();
        draw();
    }
}

void Game::update() {
    UpdateCamGoldwing(&camera, CameraMode::CAMERA_THIRD_PERSON, 0.003f, 1.f, 0.5f);

    switch (currentScreen) {
        case ScreenState::MainMenu: {
            if (CheckCollisionPointRec(GetMousePosition(), playRec) && 
                IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                currentScreen = ScreenState::Gameplay;
            }
        } break;

        case ScreenState::Gameplay: {
            // DisableCursor();

            player->update(GetFrameTime());
            player->lookAt(camera.position);
        } break;

        default: {
            EnableCursor();
        } break;
    }
}

void Game::draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    switch (currentScreen) {
        case ScreenState::MainMenu: {
            Font menuFont = am.GetFont("menuFont");
            DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
            DrawFontTrue(menuFont, "The", { screenWidth / 2.0f, 100.0f }, 100, { 255, 215, 0, 255 });
            DrawFontTrue(menuFont, "Goldwing", { screenWidth / 2.0f, 200.0f }, 100, { 255, 215, 0, 255 });
            DrawFontTrue(menuFont, "Campaign", { screenWidth / 2.0f, 300.0f }, 100, { 255, 215, 0, 255 });
            
            Color playButtonColor = CheckCollisionPointRec(GetMousePosition(), playRec) ?
                                        (Color){255, 255, 255, 125} : BLACK;
            DrawRectangleRec(playRec, playButtonColor);
            DrawRectangleLines(playRec.x, playRec.y, playRec.width, playRec.height, GRAY);
            DrawTextTrue("Play Game", screenWidth / 2, screenHeight - 197, 24, WHITE);
        } break;

        case ScreenState::Gameplay: {
            BeginMode3D(camera);
            {
                // Only draw these when using sky camera
                // DrawCubeWires(camera.position, 1, 1, 1, RED);
                // DrawLine3D(camera.position, camera.target, RED);
                
                player->draw();
                DrawGrid(10, 1.0f);
            }
            EndMode3D();

            // player->drawHealth(camera);
            DrawText(TextFormat("Camera angle to player: %.2f", player->angle), 100, 100, 24, BLACK);

        } break;
    }

    DrawFPS(10, 10);
    EndDrawing();
}
