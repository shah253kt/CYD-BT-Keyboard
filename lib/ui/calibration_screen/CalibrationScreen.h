#pragma once

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen_TT.h>

#include <unordered_map>

class CalibrationScreen final
{
public:
    void render(const std::shared_ptr<TFT_eSPI> &tft, const std::shared_ptr<XPT2046_Touchscreen> &touchScreen);

private:
    enum class Point
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    typedef std::pair<int16_t, int16_t> PointCoordinate;

    bool m_dataChanged{true};
    Point m_currentPoint{Point::TopLeft};
    std::unordered_map<Point, PointCoordinate> m_points;

    void reset();
    void checkTouch(const std::shared_ptr<XPT2046_Touchscreen> &touchScreen);
};
