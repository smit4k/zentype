#pragma once
#include <raylib.h>

class SoundManager {
  public:
    SoundManager();
    ~SoundManager();

    void Initialize();
    void PlayKeyPress();
    void PlaySpacePress();
    void PlayTabPress();
    void PlayDelete();

  private:
    Sound keyPressSound;
    Sound spacePressSound;
    Sound tabPressSound;
    Sound deleteSound;
    bool initialized;
};
