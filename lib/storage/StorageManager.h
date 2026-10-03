#pragma once

#include <EEPROM.h>

#define EEPROM_SIZE 64

class StorageManager final
{
public:
    [[nodiscard]] static StorageManager &instance();

    void init();
    [[nodiscard]] bool touchCalibrated() const;
    void setTouchCalibrated(bool calibrated) const;

private:
    bool m_eepromInitialized{false};

    StorageManager();
    StorageManager(const StorageManager &) = delete;
    StorageManager &operator=(const StorageManager &) = delete;
};
