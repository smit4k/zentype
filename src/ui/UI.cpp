#define RAYGUI_IMPLEMENTATION
#include "UI.h"
#include "raygui.h"

void UI::DrawHeader(Font customFont) {
    DrawTextEx(customFont, "zentype", (Vector2){50, 30}, 40, 2, DARKGRAY);
}

void UI::DrawTextInputBox() {
    Rectangle textBox = GetTextInputBoxBounds(); // <-- being called every frame
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
}

bool UI::DrawSettingsButton() {
    Rectangle textBox = GetTextInputBoxBounds(); // <-- also being called every frame
    
    Rectangle buttonRec = {
        textBox.x + textBox.width - BUTTON_WIDTH,
        textBox.y - BUTTON_HEIGHT - PADDING,
        (float)BUTTON_WIDTH, 
        (float)BUTTON_HEIGHT
    };
    
    return GuiButton(buttonRec, "#142#");
}

Rectangle UI::GetTextInputBoxBounds() {
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    return textBox;
}