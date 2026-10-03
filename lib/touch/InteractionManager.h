#pragma once

#include <SPI.h>
#include <XPT2046_Touchscreen.h>

#include <memory>

class InteractionManager final
{
public:
    typedef std::pair<int16_t, int16_t> PointCoordinate;

    enum class Direction
    {
        Up,
        Down,
        Left,
        Right
    };

    [[nodiscard]] static InteractionManager &instance();
    void update();
    void setRotation(uint8_t rotation);
    [[nodiscard]] std::shared_ptr<XPT2046_Touchscreen> touchScreen() const;

    void setTouchStartedCallback(std::function<void()> callback);
    void setTouchReleasedCallback(std::function<void()> callback);
    void setSwipedCallback(std::function<void(Direction)> callback);

private:
    InteractionManager();
    InteractionManager(const InteractionManager &) = delete;
    InteractionManager &operator=(const InteractionManager &) = delete;

    std::shared_ptr<SPIClass> m_touchScreenSpi;
    std::shared_ptr<XPT2046_Touchscreen> m_touchScreen;

    bool m_wasTouching{false};
    uint32_t m_touchStartTime{0};
    TS_Point m_touchStartPoint;

    std::function<void()> m_touchStartedCallback;
    std::function<void()> m_touchReleasedCallback;
    std::function<void(Direction)> m_swipedCallback;
};
