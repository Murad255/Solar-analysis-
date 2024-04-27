#pragma once
#include <Arduino.h>
#include <FastLED.h>

class  Neopixel
{
private:
int  dinPin;
int  ledsCount;
CRGB* leds;

public:
	 Neopixel(int pin, int count);
	~ Neopixel();
	void setLed(int num, byte red, byte green, byte blue,bool isShow = true);
};


Neopixel:: Neopixel(int pin, int count)
{
	CRGB newLeds[count];
	leds = newLeds;
	FastLED.addLeds<WS2812,4, GRB>(leds, count);
}

void Neopixel::setLed(int num, byte red, byte green, byte blue,bool isShow)
{
	this->leds[num] =  CRGB(red, green, blue);
	if(isShow) FastLED.show();

}



Neopixel::~ Neopixel()
{
	FastLED.clear();
}
