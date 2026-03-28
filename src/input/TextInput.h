#pragma once
#include "audio/SoundManager.h"
#include <raylib.h>
#include <string>
#include <vector>

class TextInput {
  public:
    void Update(float deltaTime, SoundManager &soundManager);
    void Draw(Rectangle bounds, Font font);
    void Restart();

  private:
    std::string typedText;
    int cursorPosition = 0;
    float cursorBlinkTimer = 0.0f;
    bool showCursor = true;
    float backspaceHoldTime = 0.0f;
    float deleteRepeatTimer = 0.0f;
    float cursorLeftHoldTime = 0.0f;
    float cursorLeftRepeatTimer = 0.0f;
    float cursorRightHoldTime = 0.0f;
    float cursorRightRepeatTimer = 0.0f;
    const float HOLD_DELAY = 0.5f;
    const float REPEAT_RATE = 0.05f;

    // Word wrapping helpers
    struct WrappedLine {
        std::string text;
        int startIndex; // Index in typedText where this line starts
        int endIndex;   // Index in typedText where this line ends
    };

    std::vector<WrappedLine> wrappedLines;
    const float TEXT_FONT_SIZE = 24.0f;
    const float LINE_SPACING = 4.0f; // Extra space between lines

    // Helper functions
    void WrapText(const std::string &text, float maxWidth, Font font);
    struct CursorLineInfo {
        int lineIndex;
        int posInLine;
    };
    CursorLineInfo GetCursorLineInfo() const;
};
