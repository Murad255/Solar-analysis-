#include <Arduino.h>
#include <SPI.h>
#include <Adafruit_ADS1X15.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "ACS712.h"

Adafruit_ADS1115 ads; /* Use this for the 16-bit version */
// Adafruit_ADS1115 ads; /* Use this for the 12-bit version */

const char *ssid = "4N1M63";                                //"Mi9T";
const char *password = "Apshaga228";                        // "mi9tphone";
const char *URL = "http://192.168.31.247:8080/Medicament/"; //"https://secure-woodland-61889.herokuapp.com/input";
const char *ContentType = "application/json";               //"text/plain";
HTTPClient http;
int16_t zero = 13336;

void setup(void)
{
  Serial.begin(9600);
  Serial.println("Hello!");
  WiFi.begin(ssid, password);

  ads.setGain(GAIN_TWOTHIRDS); // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  Serial.println("");
  Serial.println("");

  if (!ads.begin(0x48))
  {
    Serial.println("Failed to initialize ADS.");
  }
  Serial.print("Connecting to WiFi..");
  // while (WiFi.status() != WL_CONNECTED)
  // {
  //   delay(1000);
  //   Serial.print(".");
  // }
  Serial.println("#");

  Serial.println("Connected to the WiFi network");

  zero =ads.readADC_SingleEnded(0);

}

void loop()
{
  String out = "";
  /* Be sure to update this value based on the IC and the gain settings! */
  // float multiplier = 3.0F; /* ADS1015 @ +/- 6.144V gain (12-bit results) */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */


  int32_t resultsI, sumI=0;
  int32_t resultsV,sumV=0;

	//for (int i = 0; i < 10; i++) {
		sumI =ads.readADC_SingleEnded(0)-zero;
    sumV = ads.readADC_Differential_2_3();
   // delay(100);
//	}
  resultsI = sumI;///10;
  resultsV = sumV;///10;
	float I = (float)(sumI) *1.25;/// 1.0 / 65536.0 * 500.0 / 0.132;
	float V = (float)(sumV)  * multiplier*7*1.011;

  Serial.print("I = " + String(resultsI) + "(" + String(I) + "I)\t");
  Serial.println("V = " + String(resultsV) + "(" + String(V) + "V)\t");

  // out += "V:" + String(results * multiplier);
  out += " {\
    \"name\": \"outEsp\",\
    \"id\": 4,\
    \"slotId\": 5,\
    \"count\": 2,\
    \"conditionsId\": 0,\
    \"customerAcsesLevel\": 0\
  }";
  //  \"id\": 3,

  //отправка данных put запросом
  // if (WiFi.status() == WL_CONNECTED)
  // {

  //   HTTPClient http;

  //   http.begin(URL);
  //   http.addHeader("Content-Type",ContentType);

  //   // int httpResponseCode = http.PUT("PUT sent from ESP32");
  //   int httpResponseCode = http.POST(out);

  //   if (httpResponseCode > 0)
  //   {

  //     String response = http.getString();

  //     Serial.println(httpResponseCode);
  //     Serial.println(response);
  //   }
  //   else
  //   {

  //     Serial.print("Error on sending PUT Request: ");
  //     Serial.println(httpResponseCode);
  //   }

  //   http.end();
  // }
  // else
  // {
  //   Serial.println("Error in WiFi connection");
  // }
  delay(1000);


}
