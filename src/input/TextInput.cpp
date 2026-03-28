#include "TextInput.h"
#include <raylib.h>
#include <vector>

void TextInput::WrapText(const std::string &text, float maxWidth, Font font) {
    wrappedLines.clear();

    if (text.empty()) {
        wrappedLines.push_back({"", 0, 0});
        return;
    }

    std::string currentLine;
    int lineStartIndex = 0;

    for (size_t i = 0; i < text.length(); ++i) {
        currentLine += text[i];

        // Measure the current line
        Vector2 textSize = MeasureTextEx(font, currentLine.c_str(), TEXT_FONT_SIZE, 1);

        // Check if we need to wrap
        if (textSize.x >= maxWidth) {
            // Find the last space to break at (word wrapping)
            size_t lastSpacePos = currentLine.rfind(' ');

            if (lastSpacePos != std::string::npos && lastSpacePos > 0) {
                // Break at the last space
                std::string lineToAdd = currentLine.substr(0, lastSpacePos);
                wrappedLines.push_back({lineToAdd, lineStartIndex, lineStartIndex + (int)lastSpacePos});

                // Start new line with text after the space
                currentLine = currentLine.substr(lastSpacePos + 1);
                lineStartIndex += (int)lastSpacePos + 1;
                i = lineStartIndex - 1; // Adjust loop counter
            } else {
                // No space found, break at character boundary
                if (currentLine.length() > 1) {
                    std::string lineToAdd = currentLine.substr(0, currentLine.length() - 1);
                    wrappedLines.push_back({lineToAdd, lineStartIndex, lineStartIndex + (int)lineToAdd.length()});
                    currentLine = std::string(1, text[i]);
                    lineStartIndex = i;
                }
            }
        }
    }

    // Add the remaining text
    if (!currentLine.empty()) {
        wrappedLines.push_back({currentLine, lineStartIndex, (int)text.length()});
    }

    // Ensure at least one empty line if text is empty
    if (wrappedLines.empty()) {
        wrappedLines.push_back({"", 0, 0});
    }
}

TextInput::CursorLineInfo TextInput::GetCursorLineInfo() const {
    for (size_t i = 0; i < wrappedLines.size(); ++i) {
        if (cursorPosition >= wrappedLines[i].startIndex &&
            cursorPosition <= wrappedLines[i].endIndex) {
            int posInLine = cursorPosition - wrappedLines[i].startIndex;
            return {(int)i, posInLine};
        }
    }
    // If cursor is at the very end
    if (!wrappedLines.empty()) {
        const auto &lastLine = wrappedLines.back();
        return {(int)wrappedLines.size() - 1, cursorPosition - lastLine.startIndex};
    }
    return {0, 0};
}

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
    float maxWidth = bounds.width - 20; // Account for padding on both sides

    // Wrap the text based on available width
    WrapText(typedText, maxWidth, font);

    // Draw each wrapped line
    for (size_t i = 0; i < wrappedLines.size(); ++i) {
        Vector2 linePos = {x, y + i * (TEXT_FONT_SIZE + LINE_SPACING)};
        DrawTextEx(font, wrappedLines[i].text.c_str(), linePos, TEXT_FONT_SIZE, 1, DARKGRAY);
    }

    // Get cursor position information
    CursorLineInfo cursorInfo = GetCursorLineInfo();

    // Draw blinking cursor
    if (showCursor && cursorInfo.lineIndex >= 0 &&
        cursorInfo.lineIndex < (int)wrappedLines.size()) {
        const auto &cursorLine = wrappedLines[cursorInfo.lineIndex];
        std::string textBeforeCursor = cursorLine.text.substr(0, cursorInfo.posInLine);
        Vector2 cursorOffset = MeasureTextEx(font, textBeforeCursor.c_str(), TEXT_FONT_SIZE, 1);

        float cursorX = x + cursorOffset.x;
        float cursorY = y + cursorInfo.lineIndex * (TEXT_FONT_SIZE + LINE_SPACING);

        DrawRectangle(cursorX, cursorY, 2, (int)TEXT_FONT_SIZE, DARKGRAY);
    }
}

void TextInput::Restart() {
    typedText = "";
    cursorPosition = 0;
    wrappedLines.clear();
}
