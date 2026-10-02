#include "LoadingScreen.h"

namespace LoadingScreen
{
    void render(const std::shared_ptr<TFT_eSPI> &tft)
    {
        tft->fillScreen(TFT_WHITE);
        tft->setTextColor(TFT_BLACK, TFT_WHITE);
        tft->drawCentreString("Loading...", TFT_CENTER_X, TFT_CENTER_Y, 2);
    }
}
