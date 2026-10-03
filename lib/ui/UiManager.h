#pragma once

#include "Screen.h"
#include "StorageManager.h"
#include "calibration_screen/CalibrationScreen.h"

#include <TFT_eSPI.h>

#include <vector>
#include <map>
#include <memory>

class UiManager final
{
public:
    [[nodiscard]] static UiManager &instance();

    void init();
    void update();
    void setCurrentScreen(Screen screen);
    [[nodiscard]] Screen currentScreen() const;
    [[nodiscard]] std::shared_ptr<TFT_eSPI> tft() const;

private:
    UiManager();
    UiManager(const UiManager &) = delete;
    UiManager &operator=(const UiManager &) = delete;
    
    std::shared_ptr<TFT_eSPI> m_tft;

    Screen m_currentScreen;
    CalibrationScreen m_calibrationScreen;
};
