#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

#include <TFT_eSPI.h>
#include <SPI.h>
#include <font_30.h>
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);

//设置wifi的账号和密码
const char* wifiname = "HUAWEI-0409E6";
const char* wifikey = "15660090095";

//创建一个网络对象
HTTPClient https;

//连接wifi
void wificonnect();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);//设置波特率
  tft.init();
  tft.setRotation(0);
  wificonnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  clk.loadFont(font_30);
  clk.setColorDepth(8);
  clk.createSprite(50,50);
  clk.fillSprite(0x0000);
  clk.setTextDatum(CC_DATUM);   //设置文本数据
  clk.setTextColor(TFT_WHITE);
  clk.setSwapBytes(true);
  clk.println("OK!");
  clk.pushSprite(50,50);  //窗口位置
  clk.deleteSprite();
  clk.unloadFont();
}