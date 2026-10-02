#include "UiManager.h"
#include "StorageManager.h"

#include <Arduino.h>

#include <memory>

std::shared_ptr<StorageManager> storageManager = std::make_shared<StorageManager>();
UiManager uiManager(storageManager);

void setup()
{
  Serial.begin(115200);
  storageManager->init();
  uiManager.init();

  if (!storageManager->touchCalibrated()) {
    uiManager.setCurrentScreen(Screen::Calibration);
    uiManager.update();
  }
}

void loop()
{
  uiManager.update();
}
