#include "InteractionManager.h"

namespace
{
    constexpr auto TOUCH_DEBOUNCE_TIME_MS = 50;
    constexpr auto SWIPE_DISTANCE_THRESHOLD = 150;
    constexpr auto SWIPE_CROSS_AXIS_DISTANCE_THRESHOLD = 50;
    constexpr auto SWIPE_TIME_THRESHOLD_MS = 300;
}

InteractionManager::InteractionManager()
    : m_touchScreenSpi(std::make_shared<SPIClass>(VSPI)),
      m_touchScreen(std::make_shared<XPT2046_Touchscreen>(XPT2046_CS, XPT2046_IRQ))
{
    m_touchScreenSpi->begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    m_touchScreen->begin(*m_touchScreenSpi);
}

InteractionManager &InteractionManager::instance()
{
    static InteractionManager instance;
    return instance;
}

void InteractionManager::update()
{
    const auto isTouching = m_touchScreen->touched();
    const auto point = m_touchScreen->getPoint();

    if (isTouching && !m_wasTouching)
    {
        m_touchStartTime = millis();
        m_touchStartPoint = point;

        if (m_touchStartedCallback != nullptr)
        {
            m_touchStartedCallback(point);
        }
    }
    else if (!isTouching && m_wasTouching)
    {
        if (millis() - m_touchStartTime < TOUCH_DEBOUNCE_TIME_MS)
        {
            return;
        }

        if (millis() - m_touchStartTime <= SWIPE_TIME_THRESHOLD_MS)
        {
            const auto deltaX = point.x - m_touchStartPoint.x;
            const auto deltaY = point.y - m_touchStartPoint.y;
            if (abs(deltaX) >= SWIPE_DISTANCE_THRESHOLD && abs(deltaY) <= SWIPE_CROSS_AXIS_DISTANCE_THRESHOLD)
            {
                if (m_swipedCallback != nullptr)
                {
                    m_swipedCallback(deltaX > 0 ? InteractionManager::Direction::Right : InteractionManager::Direction::Left);
                }
            }
            else if (abs(deltaY) >= SWIPE_DISTANCE_THRESHOLD && abs(deltaX) <= SWIPE_CROSS_AXIS_DISTANCE_THRESHOLD)
            {
                if (m_swipedCallback != nullptr)
                {
                    m_swipedCallback(deltaY > 0 ? InteractionManager::Direction::Down : InteractionManager::Direction::Up);
                }
            }
        }

        if (m_touchReleasedCallback != nullptr)
        {
            m_touchReleasedCallback(point);
        }
    }

    m_wasTouching = isTouching;
}

void InteractionManager::setRotation(uint8_t rotation)
{
    m_touchScreen->setRotation(rotation);
}

void InteractionManager::setTouchStartedCallback(std::function<void(TS_Point)> callback)
{
    m_touchStartedCallback = callback;
}

void InteractionManager::setTouchReleasedCallback(std::function<void(TS_Point)> callback)
{
    m_touchReleasedCallback = callback;
}

void InteractionManager::setSwipedCallback(std::function<void(Direction)> callback)
{
    m_swipedCallback = callback;
}

std::shared_ptr<XPT2046_Touchscreen> InteractionManager::touchScreen() const
{
    return m_touchScreen;
}
