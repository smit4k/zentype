#include "TextInput.h"
#include <raylib.h>

void TextInput::Update(float deltaTime, SoundManager& soundManager) {
    // Handle text input
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 126) { // Printable characters
            typedText.insert(cursorPosition, 1, (char)key);
            cursorPosition++;
            soundManager.PlayKeyPress();
        }
        key = GetCharPressed();
    }

    // Handle backspace key with hold-to-repeat
    if (IsKeyDown(KEY_BACKSPACE)) {
        backspaceHoldTime += deltaTime;

        if (IsKeyPressed(KEY_BACKSPACE)) {
            // Immediate delete on first press
            if (cursorPosition > 0) {
                typedText.erase(cursorPosition - 1, 1);
                cursorPosition--;
                soundManager.PlayDelete();
            }
            deleteRepeatTimer = 0.0f;
        } else if (backspaceHoldTime >= HOLD_DELAY) {
            // Held long enough — repeat deletion
            deleteRepeatTimer += deltaTime;
            if (deleteRepeatTimer >= REPEAT_RATE && cursorPosition > 0) {
                typedText.erase(cursorPosition - 1, 1);
                cursorPosition--;
                soundManager.PlayDelete();
                deleteRepeatTimer = 0.0f;
            }
        }
    } else {
        backspaceHoldTime = 0.0f;
        deleteRepeatTimer = 0.0f;
    }

    // Move cursor with arrow keys
    if (IsKeyPressed(KEY_LEFT) && cursorPosition > 0) {
        cursorPosition--;
    }
    if (IsKeyPressed(KEY_RIGHT) && cursorPosition < (int)typedText.length()){
        cursorPosition++;
    }

    // Cursor blinking
    cursorBlinkTimer += deltaTime;
    if (cursorBlinkTimer >= 0.5f) {
        showCursor = !showCursor;
        cursorBlinkTimer = 0.0f;
    }
}

void TextInput::Draw(int x, int y) {
    // Draw text box boundary (use runtime screen size)
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);

    // Draw typed text
    DrawText(typedText.c_str(), x, y, 24, DARKGRAY);

    // Draw blinking cursor
    if (showCursor) {
        std::string textBeforeCursor = typedText.substr(0, cursorPosition);
        int cursorX = x + MeasureText(textBeforeCursor.c_str(), 24);
        DrawRectangle(cursorX, y, 2, 24, DARKGRAY);
    }
}
