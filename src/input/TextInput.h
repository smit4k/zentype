#pragma once
#include <string>
#include "audio/SoundManager.h"

class TextInput {
public:
    void Update(float deltaTime, SoundManager& soundManager);
    void Draw(int x, int y);

private:
    std::string typedText;
    int cursorPosition = 0;
    float cursorBlinkTimer = 0.0f;
    bool showCursor = true;
    float backspaceHoldTime = 0.0f;
    float deleteRepeatTimer = 0.0f;

    const float HOLD_DELAY = 0.5f;
    const float REPEAT_RATE = 0.05f;
};
