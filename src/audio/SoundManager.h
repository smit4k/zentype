#pragma once
#include "raylib.h"

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void PlayKeyPress();
    void PlayDelete();

private:
    Sound keyPressSound;
    Sound deleteSound;
};
