#pragma once

#include <SPI.h>
#include <XPT2046_Touchscreen_TT.h>

#include <memory>

class InteractionManager final
{
public:
    [[nodiscard]] static InteractionManager &instance();
    void init();
    [[nodiscard]] std::shared_ptr<XPT2046_Touchscreen> touchScreen() const;

private:
    InteractionManager();
    InteractionManager(const InteractionManager &) = delete;
    InteractionManager &operator=(const InteractionManager &) = delete;

    std::shared_ptr<SPIClass> m_touchScreenSpi;
    std::shared_ptr<XPT2046_Touchscreen> m_touchScreen;
};
