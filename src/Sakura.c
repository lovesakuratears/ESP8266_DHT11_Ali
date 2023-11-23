/**
 * @file Sakura
 * @author Sakura
 * @brief 基于esp8266温湿度读取接入AliYun
 * @version 1.0
 * @date 2023-11-23
 * 
 * @copyright Copyright (c) 2023
*/

// 引入 wifi 模块,并实例化
#include <ESP8266WiFi.h>
static WiFiClient espClient;

// 引入阿里云 IoT SDK
#include <AliyunIoTSDK.h>
// 引入DHT11模块
#include <DHT11.h>

// 设置产品和设备的信息，从阿里云设备信息里查看
#define PRODUCT_KEY "*******"
#define DEVICE_NAME "*******"
#define DEVICE_SECRET "*******"
#define REGION_ID "cn-shanghai"

// 设置 wifi 信息
#define WIFI_SSID "*******"
#define WIFI_PASSWD "*******"

//定义DHT11,蜂鸣器引脚,led
#define DHT11PIN 5
#define BPIN 4
#define LEDPIN 14

//定义温湿度
double Humidity=0;
double Temperature=0;
DHT11 dht11Sensor(DHT11PIN);

void setup()
{
    Serial.begin(115200);
    //GPIO设置
    pinMode(LEDPIN, OUTPUT);
    pinMode(BPIN, OUTPUT);
    pinMode(DHT11PIN, INPUT);
    digitalWrite(LEDPIN,HIGH); 
    digitalWrite(BPIN,HIGH);

    // 初始化 wifi
    wifiInit(WIFI_SSID, WIFI_PASSWD);
    
    // 初始化 iot，需传入 wifi 的 client，和设备产品信息
    AliyunIoTSDK::begin(espClient, PRODUCT_KEY, DEVICE_NAME, DEVICE_SECRET, REGION_ID);
    
    // 绑定一个设备属性回调，当远程修改此属性，会触发 Callback
    AliyunIoTSDK::bindData("LightSwitch", LightCallback);
    AliyunIoTSDK::bindData("AlarmSwitch", AlarmCallback);
    
}

void loop()
{
    // 读取 DHT11 温湿度
    double Humidity=dht11Sensor.readHumidity();
    double Temperature=dht11Sensor.readTemperature();
    // 读取并处理数据
    AliyunIoTSDK::loop();

    // 发送数据到云平台
    AliyunIoTSDK::send("temperature", Temperature);
    AliyunIoTSDK::send("humidity", Humidity);
}

/// @brief 初始化 wifi 连接
/// @param ssid 
/// @param passphrase 
void wifiInit(const char *ssid, const char *passphrase)
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, passphrase);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(1000);
        Serial.println("WiFi not Connect");
    }
    Serial.println("Connected to AP");
}

/// @brief Light属性修改的回调函数
/// @param p 
void LightCallback(JsonVariant p)
{
    int LightSwitch = p["LightSwitch"];
    if (LightSwitch == 1)
    {
        // 启动设备
        digitalWrite(LEDPIN,LOW); 
    } 
    if (LightSwitch == 0)
    {
        // 关闭设备
        digitalWrite(LEDPIN,HIGH); 
    } 
}

/// @brief Alarm属性修改的回调函数
/// @param p 
void AlarmCallback(JsonVariant p)
{
    // 根据属性值，控制设备
    int AlarmSwitch = p["AlarmSwitch"];
    if (AlarmSwitch == 1)
    {
        // 启动设备
        digitalWrite(BPIN,LOW); 
    } 
    if (AlarmSwitch == 0)
    {
        // 关闭设备
        digitalWrite(BPIN,HIGH); 
    } 
}  
