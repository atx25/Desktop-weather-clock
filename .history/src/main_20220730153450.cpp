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
  tft.fillScreen(TFT_BLACK);
  wificonnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  clk.loadFont(font_30);
  clk.setColorDepth(8);
  clk.createSprite(100,40);
  clk.fillSprite(0x0000);
  clk.setTextDatum(CC_DATUM);   //设置文本数据
  clk.setTextColor(TFT_WHITE);
  clk.setSwapBytes(true);
  clk.println("OK!");
  clk.pushSprite(15,15);  //窗口位置
  clk.deleteSprite();
  clk.unloadFont();
}

void wificonnect(){
  WiFi.mode(WIFI_STA); //设置8266的工作模式
  Serial.println();
  Serial.println("Connecting to ");//串口输出提示
  Serial.println(wifiname);
  WiFi.begin(wifiname,wifikey);
  WiFi.setAutoConnect(true);//设置自动连接，将wifi的账号密码保存进flash中。
  while (WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(" .");
    clk.loadFont(font_30);
    clk.setColorDepth(16);
    clk.createSprite(200,50);
    clk.fillSprite(0x0000);
    clk.setTextDatum(CC_DATUM);   //设置文本数据
    clk.setTextColor(TFT_WHITE);
    clk.setSwapBytes(true);
    clk.println("Connecting");
    clk.pushSprite(10,50);
    clk.deleteSprite();
    clk.unloadFont();
  }
  
  Serial.println();
  Serial.println("WiFi Connected IP is");
  Serial.println(WiFi.localIP());
  clk.loadFont(font_30);
  clk.setColorDepth(16);
  clk.createSprite(240,50);
  clk.fillSprite(0x0000);
  clk.setTextDatum(CC_DATUM);   //设置文本数据
  clk.setTextColor(TFT_WHITE);
  clk.setSwapBytes(true);
  clk.println(wifiname);
  clk.pushSprite(10,50);
  clk.deleteSprite();
  clk.unloadFont();
}