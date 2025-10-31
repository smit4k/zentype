#pragma once
#include <raylib.h>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void Initialize();
    void PlayKeyPress();
    void PlayDelete();
    
private:
    Sound keyPressSound;
    Sound deleteSound;
    bool initialized;
};