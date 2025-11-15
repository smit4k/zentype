#include "TextInput.h"
#include <raylib.h>
#include <vector>

void TextInput::Update(float deltaTime, SoundManager &soundManager) {
    // Handle text input
    int key = GetCharPressed();
    while (key > 0) {
        if (key >= 32 && key <= 126 && key != 32) { // Printable characters
            typedText.insert(cursorPosition, 1, (char)key);
            cursorPosition++;
            soundManager.PlayKeyPress();
        }
        key = GetCharPressed();
    }

    // Handle space key
    if (IsKeyPressed(KEY_SPACE)) {
        typedText.insert(cursorPosition, 1, ' ');
        cursorPosition++;
        soundManager.PlaySpacePress();
    }

    // Handle tab key
    if (IsKeyPressed(KEY_TAB)) {
        typedText.insert(cursorPosition, 4, ' ');
        cursorPosition += 4;
        soundManager.PlayTabPress();
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
            if (cursorRightRepeatTimer >= REPEAT_RATE &&
                cursorPosition < (int)typedText.length()) {
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

    if (IsKeyDown(KEY_LEFT_SUPER) && IsKeyPressed(KEY_BACKSPACE)) {
        Restart();
    }
}

void TextInput::Draw(Rectangle bounds, Font font) {
    float x = bounds.x + 10; // padding
    float y = bounds.y + 10; // padding

    // Draw the typed text
    DrawTextEx(font, typedText.c_str(), (Vector2){x, y}, 24, 1, DARKGRAY);

    // Calculate cursor position
    std::string textBeforeCursor = typedText.substr(0, cursorPosition);
    Vector2 cursorOffset = MeasureTextEx(font, textBeforeCursor.c_str(), 24, 1);
    float cursorX = x + cursorOffset.x;
    float cursorY = y;

    // Draw blinking cursor
    if (showCursor) {
        DrawRectangle(cursorX, cursorY, 2, 24, DARKGRAY);
    }
}

void TextInput::Restart() {
    typedText = "";
    cursorPosition = 0;
}
