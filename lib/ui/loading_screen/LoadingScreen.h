#pragma once

#include <TFT_eSPI.h>

namespace LoadingScreen
{
    void render(const std::shared_ptr<TFT_eSPI> &tft);
};
