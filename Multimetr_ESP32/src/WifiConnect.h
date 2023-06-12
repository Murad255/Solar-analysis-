#pragma once
#include <WiFi.h>
#include <DNSServer.h>
#include "pages.h"
#include "SensorLogger.h"

#define DEBUG
//ssid и пароль точки доступа
const char *ssidCon = "SensorWIFI";
const char *passwordCon = "123456789";

const char *mqtt_server = "mqtt.eclipseprojects.io"; // Имя сервера MQTT
const int mqtt_port = 1883;                          // Порт для подключения к серверу MQTT
const char *mqtt_user = "";                          // Логи от сервер
const char *mqtt_pass = "";                          // Пароль от сервера
//const char *deviceName = "ledDed";
const char *moduleType = "modules";

String wifiSsid = "";
String wifiPassword = "";
String wifiDeviceName = "";
String worcspaceName = "";
char *CwifiDeviceName = "";

using SensorLogger::DeviceSetings;
WiFiServer server(80);
int connections = 0;
void CleanStr(char* str, int len);

void WiFiStationConnected(WiFiEvent_t event, WiFiEventInfo_t info){
  connections += 1;
  #ifdef DEBUG
    Serial.print("connections: ");
    Serial.println(connections);
  #endif
}

void connect()
{
  IPAddress apIP(192, 168, 4, 7);
  DNSServer dnsServer;
  const byte DNS_PORT = 53;
  String header = "";

  //WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
 // WiFi.softAP(ssidCon, passwordCon);
  // Start access point 
  WiFi.mode(WIFI_AP);                   
  WiFi.softAP(ssidCon, passwordCon);
  WiFi.onEvent(WiFiStationConnected, ARDUINO_EVENT_WIFI_AP_STACONNECTED);

  IPAddress IP = WiFi.softAPIP();

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "www.dhome.com", IP);


  server.begin();
#ifdef DEBUG
  Serial.print("Server begin IP address: ");
  Serial.println(IP);
#endif
  while (1)
  {
    WiFiClient client = server.available(); // Listen for incoming clients

    if (client)
    {
#ifdef DEBUG
      Serial.print("."); // print a message out in the serial port
#endif
      String currentLine = ""; // make a String to hold incoming data from the client
      while (client.connected())
      { // loop while the client's connected
        if (client.available())
        {                         // if there's bytes to read from the client,
          char c = client.read(); // read a byte, then
                                  // Serial.write(c);        // print it out the serial monitor
          header += c;
          #ifdef DEBUG
                Serial.print(c); // print a message out in the serial port
          #endif
          if (c == '\n')
          { // if the byte is a newline character
            // if the current line is blank, you got two newline characters in a row.
            // that's the end of the client HTTP request, so send a response:
            if (currentLine.length() == 0)
            {
              // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
              // and a content-type so the client knows what's coming, then a blank line:
              client.println("HTTP/1.1 200 OK");
              client.println("Content-type:text/html");
              client.println("Connection: close");
              client.println();

              // ?ssid=bfdhnyt&password=grewger&name=wrgewr&grropName=ergwrw
              if (header.indexOf("ssid") >= 0 && header.indexOf("password") >= 0)
              {

                char *str;
                char *imputOptions = &header[0];
                str = strtok_r(imputOptions, "?", &imputOptions);
                imputOptions = strtok_r(imputOptions, "?", &imputOptions);
                //Serial.println(imputOptions);

                String options[] = {"", "", "", ""};
                int iter = 0;
                while ((str = strtok_r(imputOptions, "&", &imputOptions)) != NULL)
                {
                  options[iter++] = str;
                  //Serial.println(str);
                }

                for (int i = 0; i < 3; i++)
                {
                  char *str;
                  char *po = &options[i][0];
                  str = strtok_r(po, "=", &po);
                  str = strtok_r(po, "=", &po);
                  options[i] = str;
                  //Serial.println(str);
                }

                char *po = &options[3][0];
                char *str1 = strtok_r(po, " ", &po);
                str = strtok_r(str1, "=", &str1);
                str = strtok_r(str1, "=", &str1);
                options[3] = str;

                wifiSsid = options[0];
                wifiPassword = options[1];
                wifiDeviceName = options[2];
                worcspaceName = options[3];
                CwifiDeviceName = &options[3][0];
                // SensorLogger::setings.Ssid = &options[0][0];
                // wifiPassword = options[1];
                // wifiDeviceName = options[2];
                // worcspaceName = options[3];
                // CwifiDeviceName = &options[3][0];
                client.println(passwordImputPageSaved);

                delay(10);

              }
              else
              {
                #ifdef DEBUG
                      Serial.println("Sent Page"); // print a message out in the serial port
                #endif
                client.println(passwordImputPage2);
              }

              // The HTTP response ends with another blank line
              // Break out of the while loop
              break;
            }
            else
            { // if you got a newline, then clear currentLine
              currentLine = "";
            }
          }
          else if (c != '\r')
          {                   // if you got anything else but a carriage return character,
            currentLine += c; // add it to the end of the currentLine
          }
        }
      }
      // Clear the header variable
      header = "";
      if (wifiSsid.length() > 1 && wifiPassword.length() > 1)
      {
        // Close the connection
        client.stop();
        //Serial.println("Client disconnected.");
        //Serial.println("");
        break;
      }
    }
    delay(2);
  }

  //Serial.println("MQTT need.");
}

/// пробует приконектиться по сохранённым настойкам wifi, иначе вызывается connect
bool connectSetings()
{
  if (!SensorLogger::sensorLoggerIsBegin)
    SensorLogger::begin();

  WiFi.begin(SensorLogger::setings.Ssid, SensorLogger::setings.Pass);
  char *SSID;
  char *PASS;
  while (WiFi.waitForConnectResult() != WL_CONNECTED)
  {
    #ifdef DEBUG
      Serial.println("Not connected");
    #endif
    connect();
    SSID = &wifiSsid[0];
    PASS = &wifiPassword[0];
    WiFi.begin(SSID, PASS);
  }
  IPAddress apIP(192, 168, 4, 7);
  DNSServer dnsServer;
  const byte DNS_PORT = 53;
  String header = "";

  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(SensorLogger::setings.Ssid, SensorLogger::setings.Pass);

  dnsServer.setTTL(300);
  dnsServer.setErrorReplyCode(DNSReplyCode::ServerFailure);
  dnsServer.start(DNS_PORT, "www.dhome.com", apIP);

  IPAddress IP = WiFi.softAPIP();

#ifdef DEBUG
  Serial.println(IP);
#endif
  server.begin();
  CleanStr(SensorLogger::setings.Ssid,strlen(SensorLogger::setings.Ssid));
  CleanStr(SensorLogger::setings.Pass,strlen(SensorLogger::setings.Pass));
  CleanStr(SensorLogger::setings.DeviceName,strlen(SensorLogger::setings.DeviceName));
  CleanStr(SensorLogger::setings.SpaceName,strlen(SensorLogger::setings.SpaceName));

  strcat(SensorLogger::setings.Ssid, SSID);
  strcat(SensorLogger::setings.Pass, PASS);
  strcat(SensorLogger::setings.DeviceName, &wifiDeviceName[0]);
  strcat(SensorLogger::setings.SpaceName, &worcspaceName[0]);
  SensorLogger::SaveSetings();
  return true;
}


void CleanStr(char* str, int len){
  for (int i = 0; i < len; i++){
    str[i] = 0;
  }
}