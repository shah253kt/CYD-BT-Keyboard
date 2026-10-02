#pragma once

#include <EEPROM.h>

#define EEPROM_SIZE 64

class StorageManager final
{
public:
    void init();
    [[nodiscard]] bool touchCalibrated() const;
    void setTouchCalibrated(bool calibrated) const;

private:
    bool m_eepromInitialized{false};
};
