#pragma once
#include <Arduino.h>
#include <EEPROM.h>
#include <Preferences.h>
//#include "esp32-hal-ledc.h"
#define DEBUG
namespace SensorLogger
{

	struct DeviceSetings
	{
		int speed;
		int bright;
		long timout, work;
		bool isOnStatus;
		char Ssid[30];
		char Pass[30];
		char DeviceName[30];
		char SpaceName[30];
	};
#define ZcPin 18
#define thyristorPin 19

	int Pins[3] = {23, 21, 5};
	bool PinsStatus[3] = {LOW, LOW, LOW};

	bool AllPinsStatus = true;
	DeviceSetings setings;
	Preferences prefs; //энергонезависимая память
	bool sensorLoggerIsBegin = false;


	void SaveSetings();
	void dPrint(String message);
	void dPrintln(String message);

	bool setingsNotNull(DeviceSetings stng)
	{
		if (stng.speed == NULL || stng.bright == NULL ||
			&stng.Ssid == NULL || &stng.DeviceName == NULL ||
			String(stng.DeviceName).length() <= 0)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	void begin()
	{
		//	DimmableLightLinearized::setSyncPin(ZcPin);
		//	DimmableLightLinearized::begin();
		Serial.begin(9600);
		dPrintln("SensorLogger begin");

		// pinMode(Pins[0], OUTPUT);
		// digitalWrite(Pins[0], PinsStatus[0]);
		// pinMode(Pins[1], OUTPUT);
		// digitalWrite(Pins[1], PinsStatus[1]);

		// pinMode(Pins[2], OUTPUT);
		// digitalWrite(Pins[2], PinsStatus[2]);

		//EEPROM.begin(sizeof(DeviceSetings));
		//EEPROM.get(0, setings);
		// prefs.begin("DeviceName", false);
		// prefs.begin("SpaceName", false);
		// prefs.begin("bright", false);
		// prefs.begin("speed", false);
		// prefs.begin("timout", false);
		// prefs.begin("work", false);
		prefs.begin("Ssid", false);
		prefs.begin("Pass", false);

		// prefs.getBytes("DeviceName", setings.DeviceName, sizeof(setings.DeviceName));
		// prefs.getBytes("SpaceName", setings.SpaceName, sizeof(setings.SpaceName));
		prefs.getBytes("Ssid", setings.Ssid, sizeof(setings.Ssid));
		prefs.getBytes("Pass", setings.Pass, sizeof(setings.Pass));
		// setBright(prefs.getInt("bright"),false);
		// setSpeed(prefs.getInt("speed"),false);
		//setPeriod( prefs.getLong("timout"),prefs.getLong("work"),false);
		// setings.timout = prefs.getLong("timout");
		// setings.work = prefs.getLong("work");
		prefs.end();

		dPrintln("setings:");
		// dPrintln("name: " + String(setings.DeviceName));
		// dPrintln("groop: " + String(setings.SpaceName));
		dPrintln("Ssid: " + String(setings.Ssid));
		dPrintln("pass: " + String(setings.Pass));
		// dPrintln("sped: " + String(setings.speed));
		// dPrintln("bright: " + String(setings.bright));
		// dPrintln("timout: " + String(setings.timout));
		// dPrintln("work: " + String(setings.work));

		//ledcSetup(0, 50, 8);
		//	ledcAttachPin(22, 0);

		sensorLoggerIsBegin = true;
	}

	void SaveSetings()
	{
		//EEPROM.put(0, setings);
		// prefs.begin("DeviceName", false);
		// prefs.begin("SpaceName", false);
		// prefs.begin("bright", false);
		// prefs.begin("speed", false);
		// prefs.begin("timout", false);
		// prefs.begin("work", false);
		prefs.begin("Ssid", false);
		prefs.begin("Pass", false);

		// prefs.putBytes("DeviceName", setings.DeviceName, sizeof(setings.DeviceName));
		// prefs.putBytes("SpaceName", setings.SpaceName, sizeof(setings.SpaceName));
		// prefs.putInt("bright", setings.bright);
		// prefs.putInt("speed", setings.speed);
		prefs.putBytes("Ssid", setings.Ssid, sizeof(setings.Ssid));
		prefs.putBytes("Pass", setings.Pass, sizeof(setings.Pass));
		// prefs.putLong("timout", setings.timout);
		// prefs.putLong("work", setings.work);

		prefs.end();

		dPrintln("Save prefs");
	}
	///value = 0 ...100
	void setSpeed(int value, bool saveThis)
	{
		Serial.print(map(value, 0, 100, 0, 9));
		setings.speed = value;

		if (saveThis == true)
			SaveSetings();
	}

	
	void dPrint(String message)
	{
#ifdef DEBUG
		Serial.print(message);
#endif
	}

	void dPrintln(String message)
	{
#ifdef DEBUG
		Serial.println(message);
#endif
	}
}
