# ESP8266_DHT11_Ali
Arduino_ESP8266_DHT11_AliYun_LED_Buzzer（NodeMCU 3.0）

提供了一个用于基于 ESP8266 读取温湿度并接入阿里云的 Arduino 代码。
以下是一些关键点的概述：

### 关键库和依赖项：

1. **ESP8266WiFi：**
   用于 ESP8266 模块的 WiFi 连接。

2. **AliyunIoTSDK：**
   阿里云 IoT SDK 库，用于设备接入阿里云物联网平台。

3. **DHT11：**
   用于读取温湿度传感器 DHT11 的库。

4. **ArduinoJson：**
   处理 JSON 数据的库。

5. **Crypto：**
   加密相关的库。

6. **PubSubClient：**
   用于 MQTT 连接的库。

### 需要替换的信息：

- **PRODUCT_KEY、DEVICE_NAME、DEVICE_SECRET、REGION_ID：**
  从阿里云物联网平台中获取的产品信息。

- **WIFI_SSID、WIFI_PASSWD：**
  用于连接 WiFi 的 SSID 和密码。

### 主要功能：

1. **设置 GPIO 和传感器引脚：**
   设置 LED、蜂鸣器和 DHT11 传感器的引脚。

2. **初始化 WiFi 连接：**
   使用 `wifiInit` 函数连接到 WiFi。

3. **初始化 AliyunIoTSDK：**
   使用 `AliyunIoTSDK::begin` 函数初始化与阿里云 IoT 平台的连接。

4. **绑定属性回调函数：**
   使用 `AliyunIoTSDK::bindData` 函数绑定了名为 "LightSwitch" 和 "AlarmSwitch" 的设备属性的回调函数。

5. **在循环中读取温湿度数据：**
   在 `loop` 函数中读取 DHT11 传感器的温湿度数据。

6. **发送温湿度数据到云平台：**
   使用 `AliyunIoTSDK::send` 函数将温湿度数据发送到阿里云 IoT 平台。

7. **设备属性回调函数：**
   `LightCallback` 和 `AlarmCallback` 是属性修改的回调函数，用于处理设备属性的变化。

### 注意事项：

- 需要先连接到 WiFi，然后将 WiFi 的 `WiFiClient` 传递给 `AliyunIoTSDK::begin`。
  
- 需要修改 PubSubClient 的连接参数，确保其能够正确连接到 MQTT 服务器。//或者直接复制 PubSubClient.h覆盖到  \.\Documents\Arduino\libraries\PubSubClient\src

- 请注意 DHT11 传感器的引脚定义，确保其正确连接。

- 此库基于 [aoao-eth/arduino-aliyun-iot-sdk](https://github.com/aoao-eth/arduino-aliyun-iot-sdk)，你可能需要查看该库的文档了解更多详细信息。

- 平台[aliyun-iot-Platform](https://living.aliyun.com/)

请根据你的实际硬件连接和阿里云物联网平台的配置，对代码进行适当的修改。

请注意 DHT11 传感器的引脚定义，确保其正确连接。

此库似乎基于 aoao-eth/arduino-aliyun-iot-sdk，你可能需要查看该库的文档了解更多详细信息。

请根据你的实际硬件连接和阿里云物联网平台的配置，对代码进行适当的修改。


### 许可证

This code is released under the MIT License.
此代码在MIT许可证下发布。
