#include "CalibrationScreen.h"

#include "UiManager.h"
#include "InteractionManager.h"

#include <TFT_eSPI.h>
#include <XPT2046_Touchscreen.h>

namespace
{
    constexpr auto PLUS_ARM_LENGTH = 10;

    void drawPlus(const std::shared_ptr<TFT_eSPI> &tft, int16_t x, int16_t y, int16_t color = TFT_WHITE, uint8_t len = PLUS_ARM_LENGTH)
    {
        tft->drawFastVLine(x, y - len, 2 * len + 1, color);
        tft->drawFastHLine(x - len, y, 2 * len + 1, color);
    }
}

CalibrationScreen &CalibrationScreen::instance()
{
    static CalibrationScreen instance;
    return instance;
}

void CalibrationScreen::render()
{
    checkTouch();

    if (!m_dataChanged)
    {
        return;
    }

    auto tft = UiManager::instance().tft();
    tft->fillScreen(TFT_WHITE);
    tft->setTextColor(TFT_BLACK, TFT_WHITE);
    int centerX = tft->width() / 2;
    int centerY = tft->height() / 2;
    int FONT_SIZE = 2;
    tft->drawCentreString("Touch + to calibrate", centerX, centerY, FONT_SIZE);
    m_dataChanged = false;

    const auto coordinate = getCoordinate(m_currentPoint);
    drawPlus(tft, coordinate.first, coordinate.second, TFT_RED);
}

void CalibrationScreen::reset()
{
    m_dataChanged = true;
    m_currentPoint = Point::TopLeft;
    m_points.clear();
}

void CalibrationScreen::checkTouch()
{
    auto touchScreen = InteractionManager::instance().touchScreen();
    if (!touchScreen->touched())
    {
        return;
    }

    const auto point = touchScreen->getPoint();
    m_points[m_currentPoint] = {point.x, point.y};
    m_dataChanged = true;

    switch (m_currentPoint)
    {
    case Point::TopLeft:
    {
        m_currentPoint = Point::TopRight;
        break;
    }
    case Point::TopRight:
    {
        m_currentPoint = Point::BottomLeft;
        break;
    }
    case Point::BottomLeft:
    {
        m_currentPoint = Point::BottomRight;
        break;
    }
    case Point::BottomRight:
    {
        m_currentPoint = Point::TopLeft;
        break;
    }
    }

    while (touchScreen->touched())
    {
        // Wait for the touch to be released
    }
}
