#include "StorageManager.h"

namespace
{
    constexpr auto TOUCH_CALIBRATED_ADDRESS = 0x00;
}

StorageManager::StorageManager()
    : m_eepromInitialized(false)
{
    m_eepromInitialized = EEPROM.begin(EEPROM_SIZE);

    if (!m_eepromInitialized)
    {
        Serial.println("Failed to initialize EEPROM");
    }
}

StorageManager &StorageManager::instance()
{
    static StorageManager instance;
    return instance;
}

bool StorageManager::touchCalibrated() const
{
    if (!m_eepromInitialized)
    {
        Serial.println("EEPROM not initialized");
        return false;
    }

    return EEPROM.read(TOUCH_CALIBRATED_ADDRESS) == 0x01;
}

void StorageManager::setTouchCalibrated(const bool calibrated) const
{
    if (!m_eepromInitialized)
    {
        Serial.println("EEPROM not initialized");
        return;
    }

    EEPROM.write(TOUCH_CALIBRATED_ADDRESS, calibrated ? 0x01 : 0x00);

    if (EEPROM.commit())
    {
        Serial.println("Data successfully committed to flash.");
    }
    else
    {
        Serial.println("EEPROM commit failed!");
    }
}
