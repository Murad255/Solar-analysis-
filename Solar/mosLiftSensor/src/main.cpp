#include <Arduino.h>
//#include <SPI.h>
//#include <Adafruit_ADS1X15.h>
#include <WiFi.h>
#include <HTTPClient.h>

#define SENS1 35
// Adafruit_ADS1115 ads;  /* Use this for the 16-bit version */
// Adafruit_ADS1115 ads; /* Use this for the 12-bit version */

const char *ssid = "Mi9T";          //"4N1M63";
const char *password = "mi9tphone"; //"Apshaga228";
HTTPClient http;

int currentD = 0;
int dorcount;
void setup(void)
{
 WiFi.begin(ssid, password);
  Serial.begin(9600);
  Serial.println("Hello!");
 // WiFi.begin("4N1M63", "Apshaga228");
  dorcount = rand() % 1000;
  // Serial.println("Getting differential reading from AIN0 (P) and AIN1 (N)");
  // Serial.println("ADC Range: +/- 6.144V (1 bit = 3mV/ADS1015, 0.1875mV/ADS1115)");

  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
  Serial.println("");
  Serial.println("");

  // if (!ads.begin(0x48))
  // {
  //   Serial.println("Failed to initialize ADS.");
  //   // while (1);
  // }
int i = 0;
  while (WiFi.status() != WL_CONNECTED)
  {
   // if(i++>3)   WiFi.begin(ssid, password);

    delay(1000);
    Serial.println("Connecting to WiFi..");
     
  }

  Serial.println("Connected to the WiFi network");

  pinMode(SENS1, INPUT);
}

void loop()
{
  int16_t results;
  String out = "";
  /* Be sure to update this value based on the IC and the gain settings! */
  // float multiplier = 3.0F; /* ADS1015 @ +/- 6.144V gain (12-bit results) */
  float multiplier = 0.1875F; /* ADS1115  @ +/- 6.144V gain (16-bit results) */

  results = analogRead(SENS1);
  // ads.readADC_Differential_0_1();
  currentD += (rand() % 20) - 10;
  int i = rand() % 10;
  if (i > 4) dorcount++;

  // out += "{\"sensorId\":1,\"value\":" +String(results * multiplier)+ "}";
  //"V:" + String(results * multiplier);
  out += "{\
  \"sensorId\": 1,\
  \"value\": 0,\
  \"current\": " +
         String(results) + ",\
  \"door_y_data\": " +
         String(dorcount) + ",\
  \"uses_y_data\": " +
         String(results + 500) + ",\
  \"s_y_data\": " +
         String(results + currentD) + "\
}";
  //  \"timeStr\": \"string\",  \"recordTime\": 0,  \"id\": 0,


  Serial.print("Differential: ");
  Serial.println(out);


  //отправка данных put запросом
  if (WiFi.status() == WL_CONNECTED)
  {

    HTTPClient http;

    // http.begin("http://jsonplaceholder.typicode.com/posts/1");
    http.begin("http://xn--80akozvh.site:8081/OneValueSD/");
    http.addHeader("Content-Type", "application/json");

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
  }

  delay(5000);
}