#ifndef UI_H
#define UI_H

#include "raylib.h"
#include "raygui.h"

class UI {
public:
    // Initialize UI (set raygui styles if needed)
    static void Init();
    
    // Header/Title that says "zentype"
    static void DrawHeader(Font font);

    static void DrawTextInputBox();
    
    // Buttons
    static bool DrawRestartButton();
    static bool DrawSettingsButton();

    // Gets text input box boundaries
    static Rectangle GetTextInputBoxBounds();
    
private:
    static constexpr int HEADER_FONT_SIZE = 48;
    static constexpr int TEXT_FONT_SIZE = 24;
    static constexpr int STATS_FONT_SIZE = 20;
    Font customFont;
    
    static constexpr int PADDING = 20;
    static constexpr int TEXT_BOX_PADDING = 40;
    
    static constexpr int BUTTON_WIDTH = 100;
    static constexpr int BUTTON_HEIGHT = 30;
};

#endif