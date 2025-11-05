#include "TextInput.h"
#include <raylib.h>
#include <vector>

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

    // Handle tab key
    if (IsKeyPressed(KEY_TAB)) {
        typedText.insert(cursorPosition, 4, ' ');
        cursorPosition+=4;
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

void TextInput::Draw(int x, int y, Font font) {
    // Draw text box boundary
    Rectangle textBox = {50, 100, (float)GetScreenWidth() - 100.0f, (float)GetScreenHeight() - 150.0f};
    DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
    
    // Calculate maximum width for text wrapping
    float maxWidth = textBox.width - 20.0f; // Leave some padding
    float lineHeight = 30.0f; // Height between lines
    // Process text word by word for wrapping
    std::string currentLine;
    float currentY = y;
    size_t lineStart = 0;
    float cursorX = x;
    float cursorY = y;
    
    // First pass: calculate lines and find cursor position
    std::vector<std::string> lines;
    std::string tempLine;
    size_t processedChars = 0;
    
    while (processedChars < typedText.length()) {
        // Find next word boundary
        size_t nextSpace = typedText.find(' ', processedChars);
        if (nextSpace == std::string::npos) nextSpace = typedText.length();
        
        // Get the next word
        std::string word = typedText.substr(processedChars, nextSpace - processedChars + (nextSpace < typedText.length() ? 1 : 0));
        
        // Check if adding this word would exceed line width
        Vector2 newLineSize = MeasureTextEx(font, (tempLine + word).c_str(), 24, 1);
        
        if (newLineSize.x > maxWidth && !tempLine.empty()) {
            // Line is full, add it to lines
            lines.push_back(tempLine);
            
            // Check if cursor is on this line
            if (cursorPosition >= lineStart && cursorPosition <= processedChars) {
                std::string textBeforeCursor = typedText.substr(lineStart, cursorPosition - lineStart);
                Vector2 cursorOffset = MeasureTextEx(font, textBeforeCursor.c_str(), 24, 1);
                cursorX = x + cursorOffset.x;
                cursorY = y + (lines.size() - 1) * lineHeight;
            }
            
            lineStart = processedChars;
            tempLine = word;
        } else {
            tempLine += word;
        }
        
        processedChars = nextSpace + 1;
    }
    
    // Add the last line
    if (!tempLine.empty()) {
        lines.push_back(tempLine);
        if (cursorPosition >= lineStart) {
            std::string textBeforeCursor = typedText.substr(lineStart, cursorPosition - lineStart);
            Vector2 cursorOffset = MeasureTextEx(font, textBeforeCursor.c_str(), 24, 1);
            cursorX = x + cursorOffset.x;
            cursorY = y + (lines.size() - 1) * lineHeight;
        }
    }
    
    // Draw all lines
    currentY = y;
    for (const auto& line : lines) {
        DrawTextEx(font, line.c_str(), (Vector2){(float)x, currentY}, 24, 1, DARKGRAY);
        currentY += lineHeight;
    }
    
    // Draw blinking cursor
    if (showCursor) {
        DrawRectangle(cursorX, cursorY, 2, 24, DARKGRAY);
    }
}