#include "App.h"
#include <raylib.h>

App::App(int width, int height, const char* title)
    : SCREEN_WIDTH(width), SCREEN_HEIGHT(height), WINDOW_TITLE(title) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    InitAudioDevice();
    soundManager.Initialize();
    SetTargetFPS(60);
    customFont = LoadFontEx("assets/fonts/JetBrainsMono-Bold.ttf", 96, 0, 0);
    SetTextureFilter(customFont.texture, TEXTURE_FILTER_BILINEAR);
}

App::~App() {
    UnloadFont(customFont);
    CloseAudioDevice();
    CloseWindow();
}

void App::Run() {
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        Update(deltaTime);
        Draw();
    }
}

void App::Update(float deltaTime) {
    textInput.Update(deltaTime, soundManager);
}

void App::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);
    
    DrawTextEx(customFont, "zentype", (Vector2){50, 30}, 40, 2, DARKGRAY);
    
    textInput.Draw(60, 110, customFont);
    
    EndDrawing();
}