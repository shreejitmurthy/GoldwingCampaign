// #include <iostream>
// #include "raylib.h"
// #include "raymath.h"
// #include "rcamera.h"

// #include "Player.hpp"

// #include "Game.hpp"

// int main(void) {
//     const int screenWidth  = 1280;
//     const int screenHeight = 720;

//     SetConfigFlags(FLAG_MSAA_4X_HINT);
//     InitWindow(screenWidth, screenHeight, "Goldwing");
//     SetTargetFPS(60);

//     Player player(0, 0, 0);

//     const float cameraHeightOffset = player.height / 2.0f;

//     Camera3D camera;
//     camera.position   = { 0.0f, player.position.y + cameraHeightOffset, 4.0f };
//     camera.target     = {player.position.x, player.position.y + cameraHeightOffset, player.position.z};
//     camera.up         = { 0.0f, 1.0f, 0.0f };
//     camera.fovy       = 45.0f;
//     camera.projection = CAMERA_PERSPECTIVE;

//     CameraMode cameraMode = CameraMode::CAMERA_THIRD_PERSON;

//     Font menuFont = LoadFontEx("../res/fonts/MorrisRoman-Black.ttf", 24, 0, 0);
//     ScreenState currentScreen = ScreenState::MainMenu;

//     Rectangle playRec = { (screenWidth / 2) - 125, screenHeight - 200, 250, 50 };

//     while (!WindowShouldClose()) {
//         UpdateCamGoldwing(&camera, cameraMode, 0.003f, 1.f, 0.5f);

//         switch (currentScreen) {
//             case ScreenState::MainMenu: {
//                 if (CheckCollisionPointRec(GetMousePosition(), playRec) && 
//                     IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
//                     currentScreen = ScreenState::Gameplay;
//                 }
//             } break;

//             case ScreenState::Gameplay: {
//                 DisableCursor();

//                 player.update(GetFrameTime());
//             } break;

//             default: {
//                 EnableCursor();
//             } break;
//         }

//         BeginDrawing();
//         ClearBackground(RAYWHITE);

//         switch (currentScreen) {
//             case ScreenState::MainMenu: {
//                 DrawRectangle(0, 0, screenWidth, screenHeight, BLACK);
//                 DrawFontTrue(menuFont, "The", { screenWidth / 2.0f, 100.0f }, 100, { 255, 215, 0, 255 });
//                 DrawFontTrue(menuFont, "Goldwing", { screenWidth / 2.0f, 200.0f }, 100, { 255, 215, 0, 255 });
//                 DrawFontTrue(menuFont, "Campaign", { screenWidth / 2.0f, 300.0f }, 100, { 255, 215, 0, 255 });
                
//                 Color playButtonColor = CheckCollisionPointRec(GetMousePosition(), playRec) ?
//                                           (Color){255, 255, 255, 125} : BLACK;
//                 DrawRectangleRec(playRec, playButtonColor);
//                 DrawRectangleLines(playRec.x, playRec.y, playRec.width, playRec.height, GRAY);
//                 DrawTextTrue("Play Game", screenWidth / 2, screenHeight - 197, 24, WHITE);
//             } break;

//             case ScreenState::Gameplay: {
//                 BeginMode3D(camera);
//                 {
//                     player.draw();
//                     DrawGrid(10, 1.0f);
//                 }
//                 EndMode3D();

//                 player.drawHealth(camera);
//                 DrawText(TextFormat("Camera distance to player: %.2f", Vector3Distance(camera.position, camera.target)), 100, 100, 24, BLACK);

//             } break;
//         }

//         DrawFPS(10, 10);
//         EndDrawing();
//     }

//     UnloadFont(menuFont);
//     CloseWindow();

//     return 0;
// }

#include "Game.hpp"

int main() {
    Game game(1280, 720);
    game.run();
}
