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
            if (cursorPosition > 0) {
                typedText.erase(cursorPosition - 1, 1);
                cursorPosition--;
                soundManager.PlayDelete();
            }
            deleteRepeatTimer = 0.0f;
        } else if (backspaceHoldTime >= HOLD_DELAY) {
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
    
    // Handle left arrow key with hold-to-repeat
    if (IsKeyDown(KEY_LEFT)) {
        cursorLeftHoldTime += deltaTime;
        if (IsKeyPressed(KEY_LEFT)) {
            if (cursorPosition > 0) {
                cursorPosition--;
            }
            cursorLeftRepeatTimer = 0.0f;
        } else if (cursorLeftHoldTime >= HOLD_DELAY) {
            cursorLeftRepeatTimer += deltaTime;
            if (cursorLeftRepeatTimer >= REPEAT_RATE && cursorPosition > 0) {
                cursorPosition--;
                cursorLeftRepeatTimer = 0.0f;
            }
        }
    } else {
        cursorLeftHoldTime = 0.0f;
        cursorLeftRepeatTimer = 0.0f;
    }
    
    // Handle right arrow key with hold-to-repeat
    if (IsKeyDown(KEY_RIGHT)) {
        cursorRightHoldTime += deltaTime;
        if (IsKeyPressed(KEY_RIGHT)) {
            if (cursorPosition < (int)typedText.length()) {
                cursorPosition++;
            }
            cursorRightRepeatTimer = 0.0f;
        } else if (cursorRightHoldTime >= HOLD_DELAY) {
            cursorRightRepeatTimer += deltaTime;
            if (cursorRightRepeatTimer >= REPEAT_RATE && cursorPosition < (int)typedText.length()) {
                cursorPosition++;
                cursorRightRepeatTimer = 0.0f;
            }
        }
    } else {
        cursorRightHoldTime = 0.0f;
        cursorRightRepeatTimer = 0.0f;
    }
    
    // Cursor blinking
    cursorBlinkTimer += deltaTime;
    if (cursorBlinkTimer >= 0.5f) {
        showCursor = !showCursor;
        cursorBlinkTimer = 0.0f;
    }
}

void TextInput::Draw(int x, int y, Font font) {  // Add Font font parameter!
    // Draw text box boundary
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
    
    // Draw typed text with custom font
    DrawTextEx(font, typedText.c_str(), (Vector2){(float)x, (float)y}, 24, 1, DARKGRAY);
    
    // Draw blinking cursor
    if (showCursor) {
        std::string textBeforeCursor = typedText.substr(0, cursorPosition);
        Vector2 textSize = MeasureTextEx(font, textBeforeCursor.c_str(), 24, 1);
        int cursorX = x + (int)textSize.x;
        DrawRectangle(cursorX, y, 2, 24, DARKGRAY);
    }
}