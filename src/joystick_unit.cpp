#include <M5StickCPlus.h>
#include "joystick_unit.h"
#include "vibration.h"

#define JOY_ADDR 0x52 // define Joystick I2C address

void setupJoystick()
{
    Wire.begin();
}

void updateJoystick()
{
    Wire.beginTransmission(JOY_ADDR);
    Wire.write(0x00); // レジスタ開始アドレス
    Wire.endTransmission(false);
    Wire.requestFrom(JOY_ADDR, 3);
    static uint8_t x_data, y_data, button_data;

    if (Wire.available())
    { // If data is received.
        x_data = Wire.read();
        y_data = Wire.read();
        button_data = Wire.read();

        M5.Lcd.setCursor(10, 50);
        M5.Lcd.printf("X:%d      ", x_data);
        M5.Lcd.setCursor(10, 80);
        M5.Lcd.printf("Y:%d      ", y_data);
        M5.Lcd.setCursor(10, 110);
        M5.Lcd.printf("B:%d      ", button_data);
    }

    delay(200);
}