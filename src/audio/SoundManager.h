#pragma once
#include <raylib.h>

class SoundManager {
public:
    SoundManager();
    ~SoundManager();

    void Initialize();
    void PlayKeyPress();
    void PlayTabPress();
    void PlayDelete();
    
private:
    Sound keyPressSound;
    Sound tabPressSound;
    Sound deleteSound;
    bool initialized;
};