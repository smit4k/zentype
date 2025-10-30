#include "raylib.h"
#include <string>

int main() {
    const int SCREEN_WIDTH = 1200;
    const int SCREEN_HEIGHT = 700;
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "zentype");
    SetTargetFPS(60);

    InitAudioDevice();

    Sound keyPressSound = LoadSound("assets/sounds/keypress.wav");
    Sound keyDeleteSound = LoadSound("assets/sounds/delete.wav");
    
    std::string typedText = "";
    int cursorPosition = 0;
    float cursorBlinkTimer = 0.0f;
    bool showCursor = true;
    
    // Delete/backspace hold timers
    float backspaceHoldTime = 0.0f;
    float deleteHoldTime = 0.0f;
    float deleteRepeatTimer = 0.0f;
    const float HOLD_DELAY = 0.5f;  // Wait 0.5 sec before rapid delete
    const float REPEAT_RATE = 0.05f;  // Delete every 0.05 sec when held
    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();
        
        // Handle text input
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                typedText.insert(cursorPosition, 1, (char)key);
                cursorPosition++;
                PlaySound(keyPressSound);
            }
            key = GetCharPressed();
        }
        
        // Handle backspace with hold
        if (IsKeyDown(KEY_BACKSPACE)) {
            backspaceHoldTime += deltaTime;
            
            if (IsKeyPressed(KEY_BACKSPACE)) {
                // First press - delete immediately
                if (cursorPosition > 0) {
                    typedText.erase(cursorPosition - 1, 1);
                    cursorPosition--;
                    PlaySound(keyDeleteSound);
                }
                deleteRepeatTimer = 0.0f;
            } else if (backspaceHoldTime >= HOLD_DELAY) {
                // Held long enough - rapid delete
                deleteRepeatTimer += deltaTime;
                if (deleteRepeatTimer >= REPEAT_RATE && cursorPosition > 0) {
                    typedText.erase(cursorPosition - 1, 1);
                    cursorPosition--;
                    deleteRepeatTimer = 0.0f;
                }
            }
        } else {
            backspaceHoldTime = 0.0f;
            deleteRepeatTimer = 0.0f;
        }
        
        // Handle delete with hold
        if (IsKeyDown(KEY_DELETE)) {
            deleteHoldTime += deltaTime;
            
            if (IsKeyPressed(KEY_DELETE)) {
                // First press - delete immediately
                if (cursorPosition < typedText.length()) {
                    typedText.erase(cursorPosition, 1);
                }
                deleteRepeatTimer = 0.0f;
            } else if (deleteHoldTime >= HOLD_DELAY) {
                // Held long enough - rapid delete
                deleteRepeatTimer += deltaTime;
                if (deleteRepeatTimer >= REPEAT_RATE && cursorPosition < typedText.length()) {
                    typedText.erase(cursorPosition, 1);
                    deleteRepeatTimer = 0.0f;
                }
            }
        } else {
            deleteHoldTime = 0.0f;
        }
        
        // Move cursor with arrow keys
        if (IsKeyPressed(KEY_LEFT) && cursorPosition > 0) {
            cursorPosition--;
        }
        if (IsKeyPressed(KEY_RIGHT) && cursorPosition < typedText.length()) {
            cursorPosition++;
        }
        
        // Cursor blinking
        cursorBlinkTimer += deltaTime;
        if (cursorBlinkTimer >= 0.5f) {
            showCursor = !showCursor;
            cursorBlinkTimer = 0.0f;
        }
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("zentype", 50, 30, 40, DARKGRAY);
        
        Rectangle textBox = {50, 100, SCREEN_WIDTH - 100, SCREEN_HEIGHT - 150};
        DrawRectangleRoundedLinesEx(textBox, 0.02f, 16, 2.0f, LIGHTGRAY);
        
        // Draw text
        const char* text = typedText.c_str();
        DrawText(text, 60, 110, 24, DARKGRAY);
        
        // Draw cursor
        if (showCursor) {
            std::string textBeforeCursor = typedText.substr(0, cursorPosition);
            int cursorX = 60 + MeasureText(textBeforeCursor.c_str(), 24);
            DrawRectangle(cursorX, 110, 2, 24, DARKGRAY);
        }
        
        EndDrawing();
    }

    UnloadSound(keyPressSound);
    UnloadSound(keyDeleteSound);
    CloseAudioDevice();
    CloseWindow();
    return 0;
}