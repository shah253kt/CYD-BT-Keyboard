#include "UiManager.h"

#include "loading_screen/LoadingScreen.h"
#include "../touch/InteractionManager.h"

#include <lvgl.h>

namespace
{
    static uint32_t tick(void)
    {
        return millis();
    }
}

UiManager &UiManager::instance()
{
    static UiManager instance;
    return instance;
}

UiManager::UiManager()
    : m_tft(std::make_shared<TFT_eSPI>()),
      m_currentScreen(Screen::Loading)
{
}

void UiManager::init()
{
    m_tft->init();
    m_tft->invertDisplay(true);

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
        m_calibrationScreen.render(m_tft, InteractionManager::instance().touchScreen());
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

std::shared_ptr<TFT_eSPI> UiManager::tft() const
{
    return m_tft;
}
