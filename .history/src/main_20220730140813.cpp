#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//设置wifi的账号和密码
const char* wifiname = "HUAWEI-0409E6";
const char* wifikey = "15660090095";

//创建一个网络对象
HTTPClient https;

//连接wifi
void wificonnect(){
  WiFi.mode(WIFI_STA); //设置8266的工作模式
  Serial.println("Connecting to ");//串口输出提示
  Serial.println(wifiname);
  WiFi.begin(wifiname,wifikey);
  WiFi.setAutoConnect(true);//设置自动连接，将wifi的账号密码保存进flash中。
  while (WiFi.status()!=WL_CONNECTED)
  {
    Serial.print(" .");
  }
  Serial.println("WiFi Connected IP is");
  Serial.println(WiFi.localIP());
}
void setup() {
  // put your setup code here, to run once:
  wificonnect();
}

void loop() {
  // put your main code here, to run repeatedly:
}