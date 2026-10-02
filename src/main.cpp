#include "UiManager.h"

#include <Arduino.h>

UiManager uiManager;

void setup()
{
  Serial.begin(115200);
  uiManager.init();
}

void loop()
{
  // uiManager.update();
}
