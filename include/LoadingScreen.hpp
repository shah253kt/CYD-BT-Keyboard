#include "UiManager.h"

namespace LoadingScreen
{
    void render()
    {
        auto tft = UiManager::instance().tft();
        tft->fillScreen(TFT_WHITE);
        tft->setTextColor(TFT_BLACK, TFT_WHITE);
        tft->drawCentreString("Loading...", TFT_CENTER_X, TFT_CENTER_Y, 2);
        delay(1000);
    }
}
