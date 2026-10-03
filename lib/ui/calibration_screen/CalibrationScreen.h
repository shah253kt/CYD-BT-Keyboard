#pragma once

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>

#include <unordered_map>

namespace
{
    constexpr auto PLUS_MARGIN = 25;
}

class CalibrationScreen final
{
public:
    typedef std::pair<int16_t, int16_t> PointCoordinate;

    enum class Point
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    void render(const std::shared_ptr<TFT_eSPI> &tft, const std::shared_ptr<XPT2046_Touchscreen> &touchScreen);

private:
    bool m_dataChanged{true};
    Point m_currentPoint{Point::TopLeft};
    std::unordered_map<Point, PointCoordinate> m_points;

    void reset();
    void checkTouch(const std::shared_ptr<XPT2046_Touchscreen> &touchScreen);

    constexpr CalibrationScreen::PointCoordinate getCoordinate(const Point current)
    {
        switch (current)
        {
        case Point::TopLeft:
        {
            return {PLUS_MARGIN, PLUS_MARGIN};
        }
        case Point::TopRight:
        {
            return {TFT_WIDTH - PLUS_MARGIN, PLUS_MARGIN};
        }
        case Point::BottomLeft:
        {
            return {PLUS_MARGIN, TFT_HEIGHT - PLUS_MARGIN};
        }
        case Point::BottomRight:
        {
            return {TFT_WIDTH - PLUS_MARGIN, TFT_HEIGHT - PLUS_MARGIN};
        }
        }

        return {-1, -1};
    }
};
