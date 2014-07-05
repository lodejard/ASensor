/*
  ASesnor - Arduino sesnor library 
  Copyright (C)2014 Andrei Degtiarev. All right reserved
  
  You can find the latest version of the library at 
  https://github.com/AndreiDegtiarev/ASensor

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  Please see the included documents for further information.

  Commercial use of this library requires you to buy a license that
  will allow commercial use. This includes using the library,
  modified or not, as a tool to sell products.

  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#pragma once


class BMP085Sensor : public ISensor
{
#ifndef DEMO_SENSORS
	Adafruit_BMP085_Unified *_bmp ;
#endif
public:
	BMP085Sensor()
	/*	:ISensor(10085,
					   700,
					   1300,
					   700,
					   1300,
					   0,pause_length)*/
	{
#ifndef DEMO_SENSORS
 		_bmp = new Adafruit_BMP085_Unified(10085);
		if(!_bmp->begin())
		{
			/* There was a problem detecting the BMP085 ... check your connections */
			Serial.print(F("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!"));
		}
#endif
	}
	virtual const __FlashStringHelper* Name()
	{
		return F("BMP085");
	}
	virtual float LowMeasurementLimit()
	{
		return 700;
	}
	virtual float HighMeasurementLimit()
	{
		return 1300;
	}
	virtual int Precission()
	{
		return 0;
	}
	virtual bool Measure(float &data)
	{
#ifdef DEMO_SENSORS
		data=(float)rand()/RAND_MAX*100+1000;
		return true;
#else
		 sensors_event_t event;
		 _bmp->getEvent(&event);
		 if (event.pressure)
		 {
			data=event.pressure;
			return true;
		 }
		 return false;
#endif
	}
};