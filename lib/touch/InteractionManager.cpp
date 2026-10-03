#include "InteractionManager.h"

InteractionManager::InteractionManager()
    : m_touchScreenSpi(std::make_shared<SPIClass>(VSPI)),
      m_touchScreen(std::make_shared<XPT2046_Touchscreen>(XPT2046_CS, XPT2046_IRQ))
{
}

InteractionManager &InteractionManager::instance()
{
    static InteractionManager instance;
    return instance;
}

void InteractionManager::init()
{
    m_touchScreenSpi->begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    m_touchScreen->begin(*m_touchScreenSpi);
}

std::shared_ptr<XPT2046_Touchscreen> InteractionManager::touchScreen() const
{
    return m_touchScreen;
}
