#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ACS712.h"

#include <NTPClient.h>
#include <WiFiUdp.h>

#include <EEPROM.h>
#include "SensorLogger.h"
#include "WifiConnect.h"

Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
// Adafruit_ADS1115 ads; /* Use this for the 12-bit version */

// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


 const char *ssid = "XXXXXXX";  //"APOLLO";                                //"Mi9T";
 const char *password = "ZXC123456";                        // "mi9tphone";
//const char *URL = "http://192.168.31.247:8081/SensorData/"; //"https://secure-woodland-61889.herokuapp.com/input";
const char *URL = "http://185.68.21.22:8081/SensorData/"; //"https://secure-woodland-61889.herokuapp.com/input";

const char *ContentType = "application/json";               //"text/plain";
HTTPClient http;
int16_t zero = 13336;

void setup(void)
{

  SensorLogger::dPrintln("SensorLogger begin");
  SensorLogger::begin();

  char *SSID = SensorLogger::setings.Ssid;//&wifiSsid[0];
  char *PASS = SensorLogger::setings.Pass;//&wifiPassword[0];

  Serial.begin(9600);
  Serial.println("Hello!");

  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  Serial.println("");

  if (!ads.begin(0x48))
  {
    Serial.println("Failed to initialize ADS.");
  }
  Serial.print("Connecting to WiFi..");

    SensorLogger::dPrint("Connecting to ");
    SensorLogger::dPrint(SSID);
    SensorLogger::dPrint("...");

    // char *SSID = &wifiSsid[0];
    // char *PASS = &wifiPassword[0];

    WiFi.begin(SSID, PASS);

    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
      SensorLogger::dPrintln("Connecting new");
      connectSetings();
    }
    SensorLogger::dPrintln("Connected sucsesful");
  
  Serial.println("#");

  Serial.println("Connected to the WiFi network");

  zero = ads.readADC_SingleEnded(0);

  timeClient.begin();
  timeClient.setTimeOffset(3600*3);

}


void loop()
{
  String out = "";
  /* Be sure to update this value based on the IC and the gain settings! */
  // float multiplier = 3.0F; /* ADS1015 @ +/- 6.144V gain (12-bit results) */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  int32_t resultsI, sumI=0;
  int32_t resultsV,sumV=0;

	for (int i = 0; i < 10; i++) {
		sumI +=ads.readADC_SingleEnded(0)-zero;
    sumV += ads.readADC_Differential_2_3();
    delay(100);
	}
  sumI/=10.0;
  sumV/=10.0;
  resultsI = sumI;///10;
  resultsV = sumV;///10;
	float I = (float)(sumI) *1.25;/// 1.0 / 65536.0 * 500.0 / 0.132;
	float V = (float)(sumV)  * multiplier*7*1.011;

  timeClient.update();
    // We need to extract date and time
  String time = timeClient.getFormattedTime();///   getFormattedDate();
  unsigned long data = timeClient.getEpochTime() ;///   getFormattedDate();

  Serial.print("Time: "+time+"\tdata = "+String(data)+"\tI = " + String(resultsI) + "(" + String(I) + "I)\t");
  Serial.println("V = " + String(resultsV) + "(" + String(V) + "V)\t");

  // out += "V:" + String(results * multiplier);
  out += " {\
      \"cleanI\": "+String(resultsI)+",\
      \"cleanV\": "+String(resultsV)+",\
      \"normalA\": "+String(I)+",\
      \"normalV\": "+String(V)+",\
      \"time\": \""+time+"\",\
  \"timestamp\": "+String(data)+"\
  }";

  //  \"id\": 3,

 // отправка данных put запросом
  if (WiFi.status() == WL_CONNECTED)
  {
    HTTPClient http;
    http.begin(URL);
    http.addHeader("Content-Type",ContentType);

    // int httpResponseCode = http.PUT("PUT sent from ESP32");
    int httpResponseCode = http.POST(out);

    if (httpResponseCode > 0)
    {
      String response = http.getString();
      Serial.println(httpResponseCode);
      Serial.println(response);
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
  delay(9000);

}
