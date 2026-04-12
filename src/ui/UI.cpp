#include "UI.h"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

namespace {
const Color kBgTop = {246, 248, 251, 255};
const Color kBgBottom = {235, 240, 246, 255};
const Color kPanelFill = {251, 252, 254, 255};
const Color kPanelStroke = {210, 219, 229, 255};
const Color kTextStrong = {48, 58, 67, 255};
const Color kTextMuted = {122, 134, 145, 255};
const Color kDivider = {213, 220, 230, 255};
const Color kButtonFill = {247, 249, 252, 255};
const Color kButtonHover = {238, 242, 247, 255};
const Color kButtonStroke = {201, 211, 223, 255};
constexpr int kRestartIconId = 73;
constexpr int kSettingsIconId = 142;
} // namespace

Rectangle UI::cachedTextBox = {0.0f, 0.0f, 0.0f, 0.0f};
Rectangle UI::cachedRestartButtonRec = {0.0f, 0.0f, 0.0f, 0.0f};
Rectangle UI::cachedSettingsButtonRec = {0.0f, 0.0f, 0.0f, 0.0f};
int UI::lastScreenWidth = 0;
int UI::lastScreenHeight = 0;

void UI::Init() {}

void UI::UpdateCachedBounds() {
    int w = GetScreenWidth();
    int h = GetScreenHeight();

    if (lastScreenWidth == w && lastScreenHeight == h) {
        return;
    }

    float horizontalMargin = static_cast<float>(w) * 0.08f;
    if (horizontalMargin < 40.0f) {
        horizontalMargin = 40.0f;
    }
    if (horizontalMargin > 120.0f) {
        horizontalMargin = 120.0f;
    }

    const float topOffset = 128.0f;
    const float bottomOffset = 50.0f;
    cachedTextBox = {horizontalMargin, topOffset,
                     static_cast<float>(w) - horizontalMargin * 2.0f,
                     static_cast<float>(h) - topOffset - bottomOffset};

    if (cachedTextBox.height < 170.0f) {
        cachedTextBox.height = 170.0f;
    }

    const float buttonsY = cachedTextBox.y - BUTTON_SIZE - PADDING;
    cachedSettingsButtonRec = {cachedTextBox.x + cachedTextBox.width -
                                   BUTTON_SIZE,
                               buttonsY, BUTTON_SIZE, BUTTON_SIZE};
    cachedRestartButtonRec = {cachedSettingsButtonRec.x - BUTTON_SIZE - PADDING,
                              buttonsY, BUTTON_SIZE, BUTTON_SIZE};

    lastScreenWidth = w;
    lastScreenHeight = h;
}

void UI::DrawBackground() {
    DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), kBgTop,
                           kBgBottom);
}

void UI::DrawHeader(Font customFont) {
    UpdateCachedBounds();

    Vector2 headerPos = {cachedTextBox.x, 34.0f};
    DrawTextEx(customFont, "zentype", headerPos, HEADER_FONT_SIZE, 2.0f,
               kTextStrong);
    Vector2 subtitlePos = {headerPos.x + 2.0f, headerPos.y + HEADER_FONT_SIZE + 2.0f};
    DrawTextEx(customFont, "custom typing studio", subtitlePos, 18.0f, 1.0f, kTextMuted);
    DrawLineEx({headerPos.x, headerPos.y + HEADER_FONT_SIZE + 30.0f},
               {headerPos.x + 230.0f, headerPos.y + HEADER_FONT_SIZE + 30.0f},
               2.0f, kDivider);
}

void UI::DrawTextInputBox() {
    UpdateCachedBounds();

    DrawRectangleRounded(cachedTextBox, 0.03f, 24, kPanelFill);
    DrawRectangleRoundedLines(cachedTextBox, 0.03f, 24, 2.0f, kPanelStroke);
}

bool UI::IsButtonPressed(Rectangle rec) {
    return CheckCollisionPointRec(GetMousePosition(), rec) &&
           IsMouseButtonPressed(MOUSE_BUTTON_LEFT);
}

void UI::DrawButtonChrome(Rectangle rec, bool hovered) {
    DrawRectangleRounded(rec, 0.35f, 16, hovered ? kButtonHover : kButtonFill);
    DrawRectangleRoundedLines(rec, 0.35f, 16, 1.5f, kButtonStroke);
}

void UI::DrawRayguiIcon(Rectangle rec, int iconId, bool hovered) {
    const int iconX = static_cast<int>(rec.x + (rec.width - 16.0f) * 0.5f);
    const int iconY = static_cast<int>(rec.y + (rec.height - 16.0f) * 0.5f);
    GuiDrawIcon(iconId, iconX, iconY, 1, hovered ? kTextStrong : kTextMuted);
}

void UI::DrawSettingsButton() {
    UpdateCachedBounds();
    bool hovered =
        CheckCollisionPointRec(GetMousePosition(), cachedSettingsButtonRec);
    DrawButtonChrome(cachedSettingsButtonRec, hovered);
    DrawRayguiIcon(cachedSettingsButtonRec, kSettingsIconId, hovered);
}

void UI::DrawRestartButton() {
    UpdateCachedBounds();
    bool hovered =
        CheckCollisionPointRec(GetMousePosition(), cachedRestartButtonRec);
    DrawButtonChrome(cachedRestartButtonRec, hovered);
    DrawRayguiIcon(cachedRestartButtonRec, kRestartIconId, hovered);
}

bool UI::IsRestartPressed() {
    UpdateCachedBounds();
    return IsButtonPressed(cachedRestartButtonRec);
}

Rectangle UI::GetTextInputBoxBounds() {
    UpdateCachedBounds();
    return cachedTextBox;
}
