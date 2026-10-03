#include "UiManager.h"
#include "StorageManager.h"
#include "InteractionManager.h"
#include "CalibrationScreen.h"
#include "LoadingScreen.hpp"
#include "Screen.h"

#include <Arduino.h>

#include <memory>

void updateScreen();
void onScreenChanged(Screen newScreen);

void setup()
{
  Serial.begin(115200);

  auto &storageManager = StorageManager::instance();
  auto &interactionManager = InteractionManager::instance();
  auto &uiManager = UiManager::instance();
  uiManager.setScreenChangedCallback(onScreenChanged);
  interactionManager.setRotation(uiManager.tft()->getRotation());

  if (!storageManager.touchCalibrated())
  {
    uiManager.setCurrentScreen(Screen::Calibration);
  }
}

void loop()
{
  InteractionManager::instance().update();
  updateScreen();
}

void updateScreen()
{
  switch (UiManager::instance().currentScreen())
  {
  case Screen::Loading:
  {
    static bool rendered = false;
    if (!rendered)
    {
      LoadingScreen::render();
      rendered = true;
    }
    break;
  }
  case Screen::Calibration:
  {
    CalibrationScreen::instance().render();
    break;
  }
  }
}

void onScreenChanged(const Screen newScreen)
{
  switch (newScreen)
  {
  case Screen::Calibration:
  {
    CalibrationScreen::instance().reset();
    break;
  }
  }
}
