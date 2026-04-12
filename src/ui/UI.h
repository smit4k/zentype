#ifndef UI_H
#define UI_H

#include "raylib.h"

class UI {
  public:
    static void Init();
    static void DrawBackground();
    static void DrawHeader(Font font);
    static void DrawTextInputBox();

    static void DrawRestartButton();
    static void DrawSettingsButton();
    static bool IsRestartPressed();

    static Rectangle GetTextInputBoxBounds();

  private:
    static constexpr float HEADER_FONT_SIZE = 46.0f;
    static constexpr float PADDING = 14.0f;
    static constexpr float BUTTON_SIZE = 36.0f;

    static Rectangle cachedTextBox;
    static Rectangle cachedRestartButtonRec;
    static Rectangle cachedSettingsButtonRec;
    static int lastScreenWidth;
    static int lastScreenHeight;

    static void UpdateCachedBounds();
    static bool IsButtonPressed(Rectangle rec);
    static void DrawButtonChrome(Rectangle rec, bool hovered);
    static void DrawRayguiIcon(Rectangle rec, int iconId, bool hovered);
};

#endif // UI_H
