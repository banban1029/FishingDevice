#include <M5StickCPlus.h>
#include "gyro_sender.h"
#include "vibration.h"
#include "joystick_unit.h"

void setup()
{
  M5.begin();
  M5.Imu.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setTextSize(1);

  setupGyroSender();
  setupVibration();
  setupJoystick();
}

void loop()
{
  M5.update();
  confirmToWifi();
  updateGyroSender();
  updateVibration();
  updateJoystick();
  delay(10);
}