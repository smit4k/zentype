#define RAYGUI_IMPLEMENTATION
#include "UI.h"
#include "raygui.h"

void UI::DrawHeader(Font customFont) {
    const char* title = "zentype";
    Vector2 titleSize = MeasureTextEx(customFont, title, HEADER_FONT_SIZE, 2.0f);
    int screenWidth = GetScreenWidth();
    int x = (screenWidth - (int)titleSize.x) / 2;
    
    DrawTextEx(customFont, "zentype", (Vector2){50, 30}, 40, 2, DARKGRAY);
}

void UI::DrawTextInputBox() {
    Rectangle textBox = GetTextInputBoxBounds();
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
}

bool UI::DrawSettingsButton() {
    Rectangle textBox = GetTextInputBoxBounds();
    
    // Align button to the right edge of the text input box
    Rectangle buttonRec = {
        textBox.x + textBox.width - BUTTON_WIDTH,  // Right edge of text box
        textBox.y - BUTTON_HEIGHT - PADDING,        // Above text box
        (float)BUTTON_WIDTH, 
        (float)BUTTON_HEIGHT
    };
    
    return GuiButton(buttonRec, "#142#");
}
Rectangle UI::GetTextInputBoxBounds() {
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    return textBox;
}