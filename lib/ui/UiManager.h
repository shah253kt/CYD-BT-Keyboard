#pragma once

#include "Screen.h"

#include <TFT_eSPI.h>

#include <vector>
#include <map>
#include <memory>

class UiManager final
{
public:
    [[nodiscard]] static UiManager &instance();

    void setCurrentScreen(Screen screen);
    [[nodiscard]] Screen currentScreen() const;
    [[nodiscard]] std::shared_ptr<TFT_eSPI> tft() const;
    void setScreenChangedCallback(const std::function<void(Screen)> &callback);

private:
    UiManager();
    UiManager(const UiManager &) = delete;
    UiManager &operator=(const UiManager &) = delete;
    
    std::shared_ptr<TFT_eSPI> m_tft;
    Screen m_currentScreen;

    std::function<void(Screen)> m_screenChangedCallback;

    void emitScreenChanged();
};
