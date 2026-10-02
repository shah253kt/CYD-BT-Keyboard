#include "CalibrationScreen.h"

namespace
{
    constexpr auto PLUS_ARM_LENGTH = 10;
    constexpr auto PLUS_MARGIN = 25;

    void drawPlus(const std::shared_ptr<TFT_eSPI> &tft, int16_t x, int16_t y, int16_t color = TFT_WHITE, uint8_t len = PLUS_ARM_LENGTH)
    {
        tft->drawFastVLine(x, y - len, 2 * len + 1, color);
        tft->drawFastHLine(x - len, y, 2 * len + 1, color);
    }
}

void CalibrationScreen::render(const std::shared_ptr<TFT_eSPI> &tft, const std::shared_ptr<XPT2046_Touchscreen> &touchScreen)
{
    checkTouch(touchScreen);

    if (!m_dataChanged)
    {
        return;
    }

    tft->fillScreen(TFT_WHITE);
    tft->setTextColor(TFT_BLACK, TFT_WHITE);
    int centerX = tft->width() / 2;
    int centerY = tft->height() / 2;
    int FONT_SIZE = 2;
    tft->drawCentreString("Touch + to calibrate", centerX, centerY, FONT_SIZE);
    m_dataChanged = false;

    switch (m_currentPoint)
    {
    case Point::TopLeft:
    {
        drawPlus(tft, PLUS_MARGIN, PLUS_MARGIN, TFT_RED);
        break;
    }
    case Point::TopRight:
    {
        drawPlus(tft, tft->width() - PLUS_MARGIN, PLUS_MARGIN, TFT_GREEN);
        break;
    }
    case Point::BottomLeft:
    {
        drawPlus(tft, PLUS_MARGIN, tft->height() - PLUS_MARGIN, TFT_BLUE);
        break;
    }
    case Point::BottomRight:
    {
        drawPlus(tft, tft->width() - PLUS_MARGIN, tft->height() - PLUS_MARGIN, TFT_YELLOW);
        break;
    }
    }
}

void CalibrationScreen::reset()
{
    m_dataChanged = true;
    m_currentPoint = Point::TopLeft;
    m_points.clear();
}

void CalibrationScreen::checkTouch(const std::shared_ptr<XPT2046_Touchscreen> &touchScreen)
{
    if (!touchScreen->touched())
    {
        return;
    }

    Serial.println("Touch detected");

    const auto point = touchScreen->getPoint();
    m_points[m_currentPoint] = {point.x, point.y};
    m_dataChanged = true;

    switch (m_currentPoint)
    {
    case Point::TopLeft:
        m_currentPoint = Point::TopRight;
        break;
    case Point::TopRight:
        m_currentPoint = Point::BottomLeft;
        break;
    case Point::BottomLeft:
        m_currentPoint = Point::BottomRight;
        break;
    case Point::BottomRight:
        m_currentPoint = Point::TopLeft;
        break;
    }

    while (touchScreen->touched())
    {
        // Wait for the touch to be released
    }
}
