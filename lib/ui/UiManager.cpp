#include "UiManager.h"

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
    m_tft->init();
    m_tft->invertDisplay(true);

    lv_init();
    lv_tick_set_cb(tick);
}

void UiManager::setCurrentScreen(const Screen screen)
{
    if (m_currentScreen != screen)
    {
        m_currentScreen = screen;
        emitScreenChanged();
    }
}

Screen UiManager::currentScreen() const
{
    return m_currentScreen;
}

std::shared_ptr<TFT_eSPI> UiManager::tft() const
{
    return m_tft;
}

void UiManager::emitScreenChanged()
{
    if (m_screenChangedCallback != nullptr)
    {
        m_screenChangedCallback(m_currentScreen);
    }
}
