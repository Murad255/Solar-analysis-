#include <Arduino.h>
#define DEBUG

#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ACS712.h"
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <NTPClient.h>
#include <WiFiUdp.h>

#include <EEPROM.h>
#include "SensorLogger.h"
#include "WifiConnect.h"
// Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
Adafruit_MPU6050 mpu;

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// const char *URL = "http://192.168.31.198:1880/sensor";
const char *ContentType = "application/json"; //"text/plain";
HTTPClient http;
int16_t zero = 13336;
float an_past;
String getMpuData();
void Task1code(void *pvParameters);
void Task2code(void *pvParameters);

void dPrintln(String message)
	{
#ifdef DEBUG
		Serial.println(message);
#endif
	}

void setup(void)
{
  SensorLogger::dPrintln("SensorLogger begin");
  SensorLogger::begin();

  char *SSID = SensorLogger::setings.Ssid;
  char *PASS = SensorLogger::setings.Pass;

  Serial.begin(115200);
  Serial.println("Hello!");

  // ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  Serial.println("");

  // if (!ads.begin(0x48))
  // {
  //   Serial.println("Failed to initialize ADS.");
  // }
  // Try to initialize mpu!
  if (!mpu.begin())
  {
    Serial.println("Failed to find MPU6050 chip");
    while (!mpu.begin())
    {
      delay(10);
    }
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

  // setupt motion detection
  mpu.setHighPassFilter(MPU6050_HIGHPASS_0_63_HZ);
  mpu.setMotionDetectionThreshold(1);
  mpu.setMotionDetectionDuration(20);
  mpu.setInterruptPinLatch(true); // Keep it latched.  Will turn off when reinitialized.
  mpu.setInterruptPinPolarity(true);
  mpu.setMotionInterrupt(true);

  Serial.print("Connecting to WiFi..");

  SensorLogger::dPrint("Connecting to ");
  SensorLogger::dPrint(SSID);
  SensorLogger::dPrint("...");
  connectSetings();

  // WiFi.begin(SSID, PASS);

  if (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    SensorLogger::dPrintln("Connecting new");
    connectSetings();
  }
  SensorLogger::dPrintln("Connected sucsesful");

  Serial.println("#");

  Serial.println("Connected to the WiFi network");

  // zero = ads.readADC_SingleEnded(0);

  timeClient.begin();
  timeClient.setTimeOffset(3600 * 3);

  xTaskCreatePinnedToCore(Task1code, "Task1", 10000, NULL, 1, NULL, 0);
  delay(50);
  xTaskCreatePinnedToCore(Task2code, "Task2", 10000, NULL, 1, NULL, 1);
  delay(50);
}

String out = "";
volatile boolean outWrite = false;

void Task1code(void *pvParameters)
{
  Serial.println("Task1 running on core ");
  for (;;)
  {
    outWrite = true;
    out += ("," + getMpuData());
    outWrite = false;
    delay(50);
    // for (int i = 0; i < 50; i++)
    // {
    //   out += ",";
    //   out += getMpuData();
    //   delay(20);
    // }
    // out += "]";
    // out.replace("      ","");
  }
}

void Task2code(void *pvParameters)
{
  Serial.println("Task2 running on core ");
  for (;;)
  {
    // отправка данных put запросом
    if (out.length() > 1)
    {
      if (WiFi.status() == WL_CONNECTED)
      {
        while (outWrite)
        {
          dPrintln("outWrite");
          delay(5);
        }
        String tempData = out;
        out = "";
        tempData[0] = '[';
        tempData += "]";

        HTTPClient http;
        dPrintln("Sent to http://" + String(SensorLogger::setings.SpaceName) + "  " + tempData);
        http.begin("http://" + String(SensorLogger::setings.SpaceName));
        http.addHeader("Content-Type", ContentType);

        // int httpResponseCode = http.PUT("PUT sent from ESP32");
        int httpResponseCode = http.POST(tempData);

        if (httpResponseCode > 0)
        {
          // String response = http.getString();
          // Serial.println(httpResponseCode);
          // Serial.println(response);
        }
        else
        {
          Serial.print("Error on sending PUT Request: ");
          Serial.println(httpResponseCode);
        }
        http.end();
      }
      else
      {
        Serial.println("Error in WiFi connection");
        connectSetings();
      }
    }
    else
    {
      dPrintln("out = 0" );
    }
  }
}
void loop()
{
}

// void loop()
// {
//   String out = "[" + getMpuData();

//   for (int i = 0; i < 50; i++)
//   {
//     out += ",";
//     out += getMpuData();
//     delay(20);
//   }
//   out += "]";
//   out.replace("      ","");
//   //  \"id\": 3,

//   // отправка данных put запросом
//   if (out.length() > 1)
//     if (WiFi.status() == WL_CONNECTED)
//     {
//       HTTPClient http;
// #ifdef DEBUG
//       Serial.print("Sent to ");
//       Serial.println("http://" + String(SensorLogger::setings.SpaceName) + "  " + out);
// #endif
//       http.begin("http://" + String(SensorLogger::setings.SpaceName));
//       http.addHeader("Content-Type", ContentType);

//       // int httpResponseCode = http.PUT("PUT sent from ESP32");
//       int httpResponseCode = http.POST(out);

//       if (httpResponseCode > 0)
//       {
//         // String response = http.getString();
//         // Serial.println(httpResponseCode);
//         // Serial.println(response);
//       }
//       else
//       {
//         Serial.print("Error on sending PUT Request: ");
//         Serial.println(httpResponseCode);
//       }
//       http.end();
//     }
//     else
//     {
//       Serial.println("Error in WiFi connection");
//       connectSetings();
//     }
//   // delay(100);
// }

// String getAdsData()
// {
//   String out = "";
//   /* Be sure to update this value based on the IC and the gain settings! */
//   // float multiplier = 3.0F; /* ADS1015 @ +/- 6.144V gain (12-bit results) */
//   float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

//   int32_t resultsI, sumI = 0;
//   int32_t resultsV, sumV = 0;

//   for (int i = 0; i < 10; i++)
//   {
//     sumI += ads.readADC_SingleEnded(0) - zero;
//     sumV += ads.readADC_Differential_2_3();

//     // delay(10);
//   }
//   sumI /= 10.0;
//   sumV /= 10.0;
//   resultsI = sumI;                /// 10;
//   resultsV = sumV;                /// 10;
//   float I = (float)(sumI) * 1.25; /// 1.0 / 65536.0 * 500.0 / 0.132;
//   float V = (float)(sumV)*multiplier * 7 * 1.011;

//   timeClient.update();
//   // We need to extract date and time
//   String time = timeClient.getFormattedTime();    ///   getFormattedDate();
//   unsigned long data = timeClient.getEpochTime(); ///   getFormattedDate();

//    Serial.println("V = " + String(resultsV) + "\tI =" + String(resultsI) );

//   // out += "V:" + String(results * multiplier);
//   out += " {\
//       \"cleanI\": " +
//          String(resultsI) + ",\
//       \"cleanV\": " +
//          String(resultsV) + ",\
//       \"normalA\": " +
//          String(I) + ",\
//       \"normalV\": " +
//          String(V) + ",\
//       \"time\": \"" +
//          time + "\",\
//   \"timestamp\": " +
//          String(data) + "\
//   }";
// return out;
// }

String getMpuData()
{
  // if (mpu.getMotionInterruptStatus())
  // {
  /* Get new sensor events with the readings */
  float ax, ay, az;

  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  ax = a.acceleration.x;
  ay = a.acceleration.y;
  az = a.acceleration.z;

  float an = sqrt(ax * ax + ay * ay + az * az);
  float da = an_past - an;
  an_past = an;
  dPrintln(" da = " + String(da));
  timeClient.update();
  String time = timeClient.getFormattedTime();
  unsigned long data = timeClient.getEpochTime();

  return " {\
      \"ax\": " +
         String(a.acceleration.x) + ",\
      \"ay\": " +
         String(a.acceleration.y) + ",\
      \"az\": " +
         String(a.acceleration.z) + ",\
          \"da\": " +
         String(da) + ",\
       \"gx\": " +
         String(g.gyro.z) + ",\
       \"gy\": " +
         String(g.gyro.y) + ",\
       \"gx\": " +
         String(g.gyro.z) + ",\
      \"time\": \"" +
         time + "\",\
  \"timestamp\": " +
         String(data) + "\
  }";
  // }
  // else
  // {
  //   Serial.println("Error read mpu");
  //     return "";
  // }
}