#include "App.h"
#include "ui/UI.h"
#include <raylib.h>

App::App(int width, int height, const char *title)
    : SCREEN_WIDTH(width), SCREEN_HEIGHT(height), WINDOW_TITLE(title) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    UI::Init();
    InitAudioDevice();
    soundManager.Initialize();
    SetTargetFPS(GetMonitorRefreshRate(0));
    customFont = LoadFontEx("assets/fonts/Roboto-Regular.ttf", 96, 0, 0);
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
    if (UI::IsRestartPressed()) {
        textInput.Restart();
    }

    textInput.Update(deltaTime, soundManager);
}

void App::Draw() {
    BeginDrawing();
    ClearBackground({245, 248, 251, 255});
    UI::DrawBackground();

    UI::DrawHeader(customFont);
    UI::DrawTextInputBox();
    UI::DrawSettingsButton();
    UI::DrawRestartButton();
    textInput.Draw(UI::GetTextInputBoxBounds(), customFont);

    EndDrawing();
}
