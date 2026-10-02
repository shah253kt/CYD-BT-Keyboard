#include "TouchCalibrationScreen.h"

namespace TouchCalibrationScreen
{
    void update(const std::shared_ptr<TFT_eSPI> &tft)
    {
        tft->fillScreen(TFT_WHITE);
        tft->setTextColor(TFT_BLACK, TFT_WHITE);
        int centerX = tft->width() / 2;
        int centerY = tft->height() / 2;
        int FONT_SIZE = 2;
        tft->drawCentreString("Touch screen to test", centerX, centerY, FONT_SIZE);
    }
}
