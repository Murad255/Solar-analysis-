#include <Arduino.h>

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLE2902.h>
#include "Connector.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
// #include "Neopixel.h"
#define DEBUG
#define LED 2
#define NUM_LEDS 8
#define LED_PIN 4
// CRGB leds[NUM_LEDS];

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#define bleServerName "ESP32-2"


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

#define SERVICE_UUID2 "4fafc202-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID2 "beb54202-36e1-4688-b7f5-ea07361b26a8"
BLECharacteristic *pCharacteristic2;
bool deviceConnected = false;
bool oldDeviceConnected = false;
bool rqsNotify;
unsigned long prvMillis;

BLECharacteristic bmeDaCharacteristics("ca73b3ba-39f6-4ab3-91ae-186dc9577d99", BLECharacteristic::PROPERTY_NOTIFY);
BLEDescriptor bmeDaDescriptor(BLEUUID((uint16_t)0x2903));

#define INTERVAL_READ 1000
int valNotify;
#define MAX_VALNOTIFY 255
uint8_t value = 0;
Adafruit_MPU6050 mpu;
float an_past;

// Set your new MAC Address
uint8_t newMACAddress[] = {0x53, 0x43, 0xF5, 0xD3, 0x24, 0x0A};
//uint8_t newMACAddress[] = {0x44, 0x44, 0x44, 0x44, 0x44, 0x0A};

void dPrintln(String message);
String getMpuData();
void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

class MyCallbacks : public BLECharacteristicCallbacks
{
  void onWrite(BLECharacteristic *pCharacteristic)
  {
    std::string value = pCharacteristic->getValue();
    String mes = value.c_str();
    if (value.length() > 0)
    {
      Serial.println("*********");
      Serial.print("New value: ");
      for (int i = 0; i < value.length(); i++)
      {
        Serial.print((int)value[i]);
        Serial.print("\t");
      }

      Serial.println();
      Serial.println("*********");
    }

    if (value == "01")
    {
    }
    if (value == "02")
    {
    }
    else if (value[0] == 0)
    {
      char i = value[1];
    }
    else if (value[0] == 1)
    {
      Serial.println("value  1 ");
      // leds[value[1]] = CRGB(value[2], value[3], value[4]);
    }
    else if (value[0] == 2)
    {
      Serial.println("value  2 ");
      // leds[value[2]] = CRGB(value[3], value[4], value[5]);
    }
    else if (findText(mes, "mesBle").length() > 1)
    {
      int number = findText(mes, "no").toInt();
      int red = findText(mes, "red").toInt();
      int green = findText(mes, "gre").toInt();
      int blue = findText(mes, "blu").toInt();

      // FastLED.show();
    }
  }
};

class MyServerCallbacks : public BLEServerCallbacks
{
  void onConnect(BLEServer *pServer)
  {
    deviceConnected = true;
    BLEDevice::startAdvertising();

    rqsNotify = false;
    prvMillis = millis();
    Serial.println("Device connected");
  };

  void onDisconnect(BLEServer *pServer)
  {
    deviceConnected = false;

    rqsNotify = false;
    Serial.println("Device disconnected");
  }
};

void setup()
{
  Serial.begin(115200);
  pinMode(2, OUTPUT);
  Serial.println("1- Download and install an BLE scanner app in your phone");
  Serial.println("2- Scan for BLE devices in the app");
  Serial.println("3- Connect to MyESP32");
  Serial.println("4- Go to CUSTOM CHARACTERISTIC in CUSTOM SERVICE and write something");
  Serial.println("5- See the magic =)");

  while (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    delay(10);
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_5_HZ);
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  float ax = a.acceleration.x;
  float ay = a.acceleration.y;
  float az = a.acceleration.z;
  an_past = sqrt(ax * ax + ay * ay + az * az);

  Serial.println("MPU6050 Found!");

  esp_base_mac_addr_set(&newMACAddress[0]);

  BLEDevice::init(bleServerName);
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);
  pServer->setCallbacks(new MyServerCallbacks());
  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
      CHARACTERISTIC_UUID,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE);

  pCharacteristic->setCallbacks(new MyCallbacks());
  pCharacteristic->setValue("Hello World");
  pService->start();

  /////////////////

  // создаем BLE-сервис:
  BLEService *pService2 = pServer->createService(SERVICE_UUID2);
  // создаем BLE-характеристику:
  pCharacteristic2 = pService2->createCharacteristic(
      CHARACTERISTIC_UUID2,
      BLECharacteristic::PROPERTY_READ |
          BLECharacteristic::PROPERTY_WRITE |
          BLECharacteristic::PROPERTY_NOTIFY // |
                                             // BLECharacteristic::PROPERTY_INDICATE
  );
  // создаем BLE-дескриптор:
  pCharacteristic2->addDescriptor(new BLE2902());

  // da
  pService2->addCharacteristic(&bmeDaCharacteristics);
  bmeDaDescriptor.setValue("different");
  bmeDaCharacteristics.addDescriptor(new BLE2902());

  // запускаем сервис:
  pService2->start();
  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL, 0);
  delay(50);
  // xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, NULL, 1);
  delay(50);
}

void Task1code(void *pvParameters)
{
  Serial.println("Task1 running on core ");
  for (;;)
  {
    // notify changed value
    if (deviceConnected)
    {
      digitalWrite(LED, HIGH); // turn off the LED
      // delay(1000);             // bluetooth stack will go into congestion, if too many packets are sent, in 6 hours test i was able to go as low as 3ms
      // digitalWrite(LED, LOW);  // turn off the LED

      // pCharacteristic2->setValue(&value, 1);
      // pCharacteristic2->notify();
      // pCharacteristic->indicate();

      // value++;
      // outWrite = true;
      String out = getMpuData();
      dPrintln("Sent  " + out);
      bmeDaCharacteristics.setValue(out.c_str());
      bmeDaCharacteristics.notify();
      digitalWrite(LED, LOW); // turn off the LED
    }
    // disconnecting
    if (!deviceConnected && oldDeviceConnected)
    {
      delay(500); // give the bluetooth stack the chance to get things ready

      Serial.println("start advertising");
      oldDeviceConnected = deviceConnected;
      digitalWrite(LED, LOW); // turn off the LED
    }
    delay(20);
  }
}

void Task2code(void *pvParameters)
{
  Serial.println("Task2 running on core ");
  for (;;)
  {
    // // отправка данных put запросом
    // if (out.length() > 1)
    // {
    // }
    // else
    // {
    //   dPrintln("out = 0");
    // }
  }
}
void loop()
{
}
////////////////////////////////////////////

String getMpuData()
{
  /* Get new sensor events with the readings */
  float ax, ay, az;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x*1000;
  ay = a.acceleration.y*1000;
  az = a.acceleration.z*1000;

  float an = sqrt(ax * ax + ay * ay + az * az);
  float da = abs(an_past - an);
  an_past = an;
  dPrintln(" da = " + String(da));
  unsigned long time = millis();

  String xyz = String(ax)+';'+String(ay)+';'+String(az);
  pCharacteristic2->setValue(xyz.c_str());
  pCharacteristic2->notify();

  return String(da);

  // "x" +String((int)a.acceleration.x*10) + ",\
  //     \"ay\": " +
  //        String(a.acceleration.y) + ",\
  //     \"az\": " +
  //        String(a.acceleration.z) + ",\
  //         \"da\": " +
  //        String(da) + ",\
  //     \"time\": \"" +
  //        time + "}";
}

void dPrintln(String message)
{
#ifdef DEBUG
  Serial.println(message);
#endif
}