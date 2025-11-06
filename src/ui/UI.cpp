#define RAYGUI_IMPLEMENTATION
#include "UI.h"

void UI::DrawHeader(Font customFont) {
    const char* title = "zentype";
    Vector2 titleSize = MeasureTextEx(customFont, title, HEADER_FONT_SIZE, 2.0f);
    int screenWidth = GetScreenWidth();
    int x = (screenWidth - (int)titleSize.x) / 2;
    
    DrawTextEx(customFont, "zentype", (Vector2){50, 30}, 40, 2, DARKGRAY);
}

void UI::DrawTextInputBox() {
    Rectangle textBox = GetTextBoxBounds();
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
}

Rectangle UI::GetTextBoxBounds() {
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    return textBox;
}