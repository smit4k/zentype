#ifndef UI_H
#define UI_H

#include "raylib.h"

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
    // Sizing constants
    static constexpr float HEADER_FONT_SIZE = 48.0f;
    static constexpr float TEXT_FONT_SIZE = 24.0f;
    static constexpr float STATS_FONT_SIZE = 20.0f;

    // Layout constants
    static constexpr float PADDING = 20.0f;
    static constexpr float TEXT_BOX_PADDING = 40.0f;
    static constexpr float BUTTON_WIDTH = 32.0f;
    static constexpr float BUTTON_HEIGHT = 32.0f;

    // Cache
    static Rectangle cachedTextBox;
    static Rectangle cachedButtonRec;
    static int lastScreenWidth;
    static int lastScreenHeight;

    // Helper to update cached bounds
    static void UpdateCachedBounds();
};

#endif // UI_H
