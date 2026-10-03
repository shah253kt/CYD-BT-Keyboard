#pragma once

#include <unordered_map>
#include <memory>

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

    [[nodiscard]] static CalibrationScreen &instance();
    void render();

private:
    bool m_dataChanged{true};
    Point m_currentPoint{Point::TopLeft};
    std::unordered_map<Point, PointCoordinate> m_points;

    CalibrationScreen() = default;
    CalibrationScreen(const CalibrationScreen &) = delete;
    CalibrationScreen &operator=(const CalibrationScreen &) = delete;

    void reset();
    void checkTouch();

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
