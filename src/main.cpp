#include <M5StickCPlus.h>
#include "gyro_sender.h"

void setup()
{
  M5.begin();
  M5.Imu.Init();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setTextFont(4);
  M5.Lcd.setTextSize(1);

  setupGyroSender();
}

void loop()
{
  M5.update();
  confirmToWifi();
  updateGyroSender();
  delay(10);
}