#pragma once

#include "Screen.h"
#include "StorageManager.h"
#include "calibration_screen/CalibrationScreen.h"

#include <SPI.h>
#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>

#include <vector>
#include <map>
#include <memory>

class UiManager final
{
public:
    UiManager(const std::shared_ptr<StorageManager> &storageManager);

    void init();
    void update();
    void setCurrentScreen(Screen screen);
    [[nodiscard]] Screen currentScreen() const;

private:
    std::shared_ptr<StorageManager> m_storageManager;

    std::shared_ptr<TFT_eSPI> m_tft;
    std::shared_ptr<SPIClass> m_touchScreenSpi;
    std::shared_ptr<XPT2046_Touchscreen> m_touchScreen;

    Screen m_currentScreen;
    CalibrationScreen m_calibrationScreen;
};
