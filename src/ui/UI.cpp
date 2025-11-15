#define RAYGUI_IMPLEMENTATION
#include "UI.h"
#include "raygui.h"

Rectangle UI::cachedTextBox = {0.0f, 0.0f, 0.0f, 0.0f};
Rectangle UI::cachedRestartButtonRec = {0.0f, 0.0f, 0.0f, 0.0f};
Rectangle UI::cachedSettingsButtonRec = {0.0f, 0.0f, 0.0f, 0.0f};

int UI::lastScreenWidth = 0;
int UI::lastScreenHeight = 0;

void UI::Init() {
    // Optional: raygui custom styling
    // GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

void UI::UpdateCachedBounds() {
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    if (lastScreenWidth != w || lastScreenHeight != h) {

        cachedTextBox = {50.0f, 100.0f, static_cast<float>(w) - 100.0f,
                         static_cast<float>(h) - 150.0f};

        cachedSettingsButtonRec = {cachedTextBox.x + cachedTextBox.width -
                                       BUTTON_WIDTH,
                                   cachedTextBox.y - BUTTON_HEIGHT - PADDING,
                                   BUTTON_WIDTH, BUTTON_HEIGHT};

        cachedRestartButtonRec = {
            cachedSettingsButtonRec.x - BUTTON_WIDTH - PADDING,
            cachedSettingsButtonRec.y, BUTTON_WIDTH, BUTTON_HEIGHT};

        lastScreenWidth = w;
        lastScreenHeight = h;
    }
}

void UI::DrawHeader(Font customFont) {
    Vector2 headerPos = {50.0f, 30.0f};
    DrawTextEx(customFont, "zentype", headerPos, HEADER_FONT_SIZE, 2, DARKGRAY);
}

void UI::DrawTextInputBox() {
    UpdateCachedBounds();

    DrawRectangleRoundedLines(cachedTextBox, 0.02f, 16, 2.0f, LIGHTGRAY);
}

bool UI::DrawSettingsButton() {
    UpdateCachedBounds();
    return GuiButton(cachedSettingsButtonRec, "#142#");
}

bool UI::DrawRestartButton() {
    UpdateCachedBounds();
    return GuiButton(cachedRestartButtonRec, "#73#");
}

Rectangle UI::GetTextInputBoxBounds() {
    UpdateCachedBounds();
    return cachedTextBox;
}
