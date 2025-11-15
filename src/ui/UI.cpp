#define RAYGUI_IMPLEMENTATION
#include "UI.h"
#include "raygui.h"

Rectangle UI::cachedTextBox = {0};
Rectangle UI::cachedButtonRec = {0};
int UI::lastScreenWidth = 0;
int UI::lastScreenHeight = 0;

void UI::Init() {
    // Set raygui styles here if needed
    // GuiSetStyle(DEFAULT, TEXT_SIZE, 20);
}

void UI::UpdateCachedBounds() {
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    // Only recalculate if window resized
    if (lastScreenWidth != w || lastScreenHeight != h) {
        cachedTextBox = {50, 100, (float)w - 100.0f, (float)h - 150.0f};

        cachedButtonRec = {cachedTextBox.x + cachedTextBox.width - BUTTON_WIDTH,
                           cachedTextBox.y - BUTTON_HEIGHT - PADDING,
                           BUTTON_WIDTH, BUTTON_HEIGHT};

        lastScreenWidth = w;
        lastScreenHeight = h;
    }
}

void UI::DrawHeader(Font customFont) {
    DrawTextEx(customFont, "zentype", (Vector2){50, 30}, HEADER_FONT_SIZE, 2,
               DARKGRAY);
}

void UI::DrawTextInputBox() {
    UpdateCachedBounds();
    DrawRectangleRoundedLinesEx(cachedTextBox, 0.02f, 16, 2.0f, LIGHTGRAY);
}

bool UI::DrawSettingsButton() {
    UpdateCachedBounds();
    return GuiButton(cachedButtonRec, "#142#");
}

bool UI::DrawRestartButton() {
    // TODO: Implement restart button
    return false;
}

Rectangle UI::GetTextInputBoxBounds() {
    UpdateCachedBounds();
    return cachedTextBox;
}
