#pragma once

#include <XPT2046_Touchscreen.h>

#include <unordered_map>
#include <memory>

namespace
{
    constexpr auto PLUS_MARGIN = 25;
}

class CalibrationScreen final
{
public:
    enum class Point
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    [[nodiscard]] static CalibrationScreen &instance();
    void reset();
    void render();

private:
    bool m_dataChanged{true};
    Point m_currentPoint{Point::TopLeft};
    std::unordered_map<Point, TS_Point> m_points;

    CalibrationScreen() = default;
    CalibrationScreen(const CalibrationScreen &) = delete;
    CalibrationScreen &operator=(const CalibrationScreen &) = delete;

    void onTouchReleased(const TS_Point point);

    constexpr TS_Point getCoordinate(const Point current)
    {
        switch (current)
        {
        case Point::TopLeft:
        {
            return {PLUS_MARGIN, PLUS_MARGIN, 0};
        }
        case Point::TopRight:
        {
            return {TFT_WIDTH - PLUS_MARGIN, PLUS_MARGIN, 0};
        }
        case Point::BottomLeft:
        {
            return {PLUS_MARGIN, TFT_HEIGHT - PLUS_MARGIN, 0};
        }
        case Point::BottomRight:
        {
            return {TFT_WIDTH - PLUS_MARGIN, TFT_HEIGHT - PLUS_MARGIN, 0};
        }
        }

        return {};
    }
};
