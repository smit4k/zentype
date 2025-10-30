#include "App.h"
#include "raylib.h"

App::App(int width, int height, const char* title)
    : screenWidth(width), screenHeight(height), windowTitle(title) {
    InitWindow(screenWidth, screenHeight, windowTitle);
    InitAudioDevice();
    SetTargetFPS(60);
}

App::~App() {
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

    DrawText("zentype", 50, 30, 40, DARKGRAY);
    textInput.Draw(60, 110);

    EndDrawing();
}
