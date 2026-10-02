#include "UiManager.h"

#include "touch_calibration_screen/TouchCalibrationScreen.h"

UiManager::UiManager() : m_tft(std::make_shared<TFT_eSPI>()), m_touchscreenSpi(std::make_shared<SPIClass>(VSPI)), m_touchscreen(std::make_shared<XPT2046_Touchscreen>(XPT2046_CS, XPT2046_IRQ)), m_currentScreen(Screen::Loading)
{
}

void UiManager::init()
{
    m_tft->init();

    m_touchscreenSpi->begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    m_touchscreen->begin(*m_touchscreenSpi);
    m_touchscreen->setRotation(m_tft->getRotation());

    Serial.println("UI Manager initialized");
    update();
}

void UiManager::update()
{
    switch (m_currentScreen)
    {
    case Screen::Loading:
    {
        TouchCalibrationScreen::update(m_tft);
        break;
    }
    }
}

void UiManager::setCurrentScreen(const Screen screen)
{
    m_currentScreen = screen;
}

Screen UiManager::currentScreen() const
{
    return m_currentScreen;
}
