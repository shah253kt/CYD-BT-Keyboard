#pragma once

#include "Screen.h"

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>

#include <vector>
#include <map>
#include <memory>

class UiManager final
{
public:
    UiManager();

    void init();
    void update();
    void setCurrentScreen(Screen screen);
    [[nodiscard]] Screen currentScreen() const;

private:
    std::shared_ptr<TFT_eSPI> m_tft;
    std::shared_ptr<SPIClass> m_touchscreenSpi;
    std::shared_ptr<XPT2046_Touchscreen> m_touchscreen;

    Screen m_currentScreen;
};
