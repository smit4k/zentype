#pragma once
#include "input/TextInput.h"
#include "audio/SoundManager.h"

class App {
public:
    App(int width, int height, const char* title);
    ~App();

    void Run();  // main game loop

private:
    int screenWidth;
    int screenHeight;
    const char* windowTitle;

    TextInput textInput;
    SoundManager soundManager;

    void Update(float deltaTime);
    void Draw();
};
