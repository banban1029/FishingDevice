#include <M5StickCPlus.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include "wifi_status.h" // SSIDとパスワードをここから読み込む
#include "gyro_sender.h"

unsigned long lastReconnectAttempt = 0;
WiFiUDP udp;

void setupGyroSender()
{
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(300);
        M5.Lcd.print(".");
    }
    M5.Lcd.println("WiFi Connected");
    M5.Lcd.setCursor(10, 30);
    M5.Lcd.println("  gx     gy     gz");
}

void updateGyroSender()
{
    float gx, gy, gz;
    M5.IMU.getGyroData(&gx, &gy, &gz); // deg/s

    // 静止時に補正
    float offsetX = -3.0;
    float offsetY = -3.0;
    float offsetZ = 10.0;
    gx -= offsetX;
    gy -= offsetY;
    gz -= offsetZ;

    char buf[64];
    snprintf(buf, sizeof(buf), "%.1f,%.1f,%.1f", gx, gy, gz);
    udp.beginPacket(host_ip, host_port);
    udp.print(buf);
    udp.endPacket();

    // M5.Lcd.setCursor(10, 70);
    // M5.Lcd.printf("%5.1f ,%5.1f ,%5.1f ", gx, gy, gz);

    if (M5.BtnA.wasPressed())
    {
        udp.beginPacket(host_ip, host_port);
        udp.print("RESET");
        udp.endPacket();
    }

    delay(30);
}

void confirmToWifi()
{
    // WiFi接続状態を常に確認し、切れていたら再接続
}