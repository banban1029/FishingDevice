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
    static uint8_t x_data, y_data, button_data, offsetX, offsetY, scaleX, scaleY;

    if (Wire.available())
    { // If data is received.
        x_data = Wire.read();
        y_data = Wire.read();
        button_data = Wire.read();

        // fix offset for center point
        offsetX = 129;
        offsetY = 138;
        x_data += 126 - offsetX;
        y_data += 126 - offsetY;

        //  fix offset for scale
        int x_min = 5, x_max = 249;
        int y_min = 3, y_max = 220;
        scaleX = map(x_data, x_min, x_max, 0, 255);
        scaleY = map(y_data, y_min, y_max, 0, 255);

        M5.Lcd.setCursor(10, 50);
        M5.Lcd.printf("X:%d      ", scaleX);
        M5.Lcd.setCursor(10, 80);
        M5.Lcd.printf("Y:%d      ", scaleY);
        M5.Lcd.setCursor(10, 110);
        M5.Lcd.printf("B:%d      ", button_data);
    }

    delay(200);
}