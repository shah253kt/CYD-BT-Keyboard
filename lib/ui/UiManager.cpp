#include "UiManager.h"

#include "loading_screen/LoadingScreen.h"

#include <lvgl.h>

namespace
{
    static uint32_t tick(void)
    {
        return millis();
    }
}

UiManager::UiManager(const std::shared_ptr<StorageManager> &storageManager)
    : m_storageManager(storageManager),
      m_tft(std::make_shared<TFT_eSPI>()),
      m_touchScreenSpi(std::make_shared<SPIClass>(VSPI)),
      m_touchScreen(std::make_shared<XPT2046_Touchscreen>(XPT2046_CS, XPT2046_IRQ)),
      m_currentScreen(Screen::Loading)
{
}

void UiManager::init()
{
    m_tft->init();
    m_tft->invertDisplay(true);

    m_touchScreenSpi->begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    m_touchScreen->begin(*m_touchScreenSpi);
    m_touchScreen->setRotation(m_tft->getRotation());

    lv_init();
    lv_tick_set_cb(tick);

    Serial.println("UI Manager initialized");
    update();
}

void UiManager::update()
{
    switch (m_currentScreen)
    {
    case Screen::Loading:
    {
        static bool rendered = false;
        if (!rendered)
        {
            LoadingScreen::render(m_tft);
            rendered = true;
        }
        break;
    }
    case Screen::Calibration:
    {
        m_calibrationScreen.render(m_tft, m_touchScreen);
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
