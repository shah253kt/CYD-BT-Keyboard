#pragma once

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>

namespace TouchCalibrationScreen
{
    void update(const std::shared_ptr<TFT_eSPI> &tft);
};
