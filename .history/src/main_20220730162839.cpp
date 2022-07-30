#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>


#include <TFT_eSPI.h>
#include <SPI.h>
#include <font_30.h>
//设置屏幕
TFT_eSPI tft = TFT_eSPI();
TFT_eSprite clk = TFT_eSprite(&tft);

#include <ArduinoJson.h>
//创建一个网络对象
WiFiClientSecure client;
HTTPClient https;
//连接天气服务器
void getweather();
//设置天气参数
String location="411627";//太康
String key="d4055a0ac0848d29ab8bb6e4ad498d7a";//密匙
String extensions="base";//base 实时天气，all 预报天气

//设置wifi的账号和密码
const char* wifiname = "HUAWEI-0409E6";
const char* wifikey = "15660090095";
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
  getweather();
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
//解析天气程序
void putweather(const char* input){
  const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(9) + 200;
  DynamicJsonBuffer jsonBuffer(capacity);

  JsonObject& root = jsonBuffer.parseObject(input);

  const char* status = root["status"]; // "1"
  const char* count = root["count"]; // "1"
  const char* info = root["info"]; // "OK"
  const char* infocode = root["infocode"]; // "10000"

  JsonObject& lives_0 = root["lives"][0];
  const char* lives_0_province = lives_0["province"]; // "河南"
  const char* lives_0_city = lives_0["city"]; // "太康县"
  const char* lives_0_adcode = lives_0["adcode"]; // "411627"
  const char* lives_0_weather = lives_0["weather"]; // "阴"
  const char* lives_0_temperature = lives_0["temperature"]; // "32"
  const char* lives_0_winddirection = lives_0["winddirection"]; // "无风向"
  const char* lives_0_windpower = lives_0["windpower"]; // "≤3"
  const char* lives_0_humidity = lives_0["humidity"]; // "63"
  const char* lives_0_reporttime = lives_0["reporttime"]; // "2022-07-30 15:30:12"
  Serial.println();
  Serial.println(lives_0_province);
}
void getweather(){
  client.setInsecure();//连接服务器不验证身份
  client.setTimeout(5000);//设置服务器连接超时
  Serial.println("[HTTPS] begin...");
  String url = "https://restapi.amap.com/v3/weather/weatherInfo?&city="
                + location + "&key=" + key + "&extensions=" + extensions;
  if(https.begin(client,url)){
    Serial.println("[HTTPS] GET...");
    int httpCode = https.GET();
    if(httpCode >= 0){
      Serial.printf("[HTTPS] GET... code: %d\n", httpCode);
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) { // 服务器响应
        String str = https.getString();
        Serial.printf(str.c_str());
        putweather(str.c_str());
      }
    } else { // 错误返回负值
      Serial.printf("[HTTPS] GET... failed, error: %s\n", https.errorToString(httpCode).c_str());
    }
    https.end();
    }
  else { // HTTPS连接失败
    Serial.printf("[HTTPS] Unable to connect\n");
  }
}