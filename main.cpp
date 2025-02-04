#include <iostream>

#include "raylib.h"
#include "raymath.h"

void DrawFontTrue(Font font, const char* text, Vector2 truePosition, float size, Color colour) {
    DrawTextEx(
        font,
        text,
        Vector2Subtract(truePosition, Vector2Scale(MeasureTextEx(font, text, size, 2), 0.5)),
        size,
        4,
        colour
    );
}

void DrawTextTrue(const char* text, int x, int y, int size, Color color) {
    DrawText(text, x - MeasureText(text, size) / 2, y + GetFontDefault().baseSize, size, WHITE);
}

enum class ScreenState {
    Menu,
    Gameplay
};

int main() {
    const int screenWidth = 1280;
    const int screenHeight = 720;

    InitWindow(screenWidth, screenHeight, "Goldwing");
    SetTargetFPS(60);

    Font menuFont = LoadFontEx("../res/MorrisRoman-Black.ttf", 24, 0, 0);

    ScreenState currentScreen = ScreenState::Menu;

    Rectangle playRec = { (screenWidth / 2) - 125, screenHeight - 200, 250, 50 };

    while (!WindowShouldClose()) {
        switch (currentScreen) {
            case ScreenState::Menu:
            {
                // TODO: Update menu stuff here
                
                if (CheckCollisionPointRec(GetMousePosition(), playRec) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    currentScreen = ScreenState::Gameplay;
                }

            } break;

            case ScreenState::Gameplay:
            {
                // TODO: Update gameplay stuff here
            } break;
        }

        BeginDrawing();
        {
            ClearBackground(BLACK);

            switch (currentScreen) {
                case ScreenState::Menu:
                {
                    DrawFontTrue(menuFont, "The", {screenWidth / 2, 100}, 100, {255, 215, 0, 255});
                    DrawFontTrue(menuFont, "Goldwing", {screenWidth / 2, 200}, 100, {255, 215, 0, 255});
                    DrawFontTrue(menuFont, "Campaign", {screenWidth / 2, 300}, 100, {255, 215, 0, 255});

                    DrawRectangleRec(
                        playRec, 
                        CheckCollisionPointRec(GetMousePosition(), playRec) ? (Color){255, 255, 255, 125} : BLACK
                    );
                    DrawRectangleLines((screenWidth / 2) - 125, screenHeight - 200, 250, 50, GRAY);
                    DrawTextTrue("Play Game", screenWidth / 2, screenHeight - 197, 24, WHITE);

                } break;

                case ScreenState::Gameplay:
                {
                    // TODO: Draw gameplay stuff here
                    DrawTextTrue("Gameplay State (coming soon)", screenWidth / 2, screenHeight - 197, 24, WHITE);
                } break;
            }
        }
        EndDrawing();
    }

    UnloadFont(menuFont);
    CloseWindow();

    return 0;
}
