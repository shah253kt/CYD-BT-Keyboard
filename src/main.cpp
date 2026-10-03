#include "UiManager.h"
#include "StorageManager.h"
#include "InteractionManager.h"

#include <Arduino.h>

#include <memory>

void setup()
{
  Serial.begin(115200);
  
  auto &storageManager = StorageManager::instance();
  storageManager.init();
  
  auto &interactionManager = InteractionManager::instance();
  interactionManager.init();
  
  auto &uiManager = UiManager::instance();
  uiManager.init();
  interactionManager.touchScreen()->setRotation(uiManager.tft()->getRotation());

  if (!storageManager.touchCalibrated())
  {
    uiManager.setCurrentScreen(Screen::Calibration);
    uiManager.update();
  }
}

void loop()
{
  UiManager::instance().update();
}
