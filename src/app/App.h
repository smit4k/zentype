#pragma once
#include "audio/SoundManager.h"
#include "input/TextInput.h"

class App {
  public:
    App(int width, int height, const char *title);
    ~App();

    void Run();

  private:
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const char *WINDOW_TITLE;
    TextInput textInput;
    SoundManager soundManager;
    Font customFont;

    void Update(float deltaTime);
    void Draw();
};
