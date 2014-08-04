#pragma once
/*
  AFrame - Arduino framework library for ASensor and AWind libraries
  Copyright (C)2014 Andrei Degtiarev. All right reserved
  
  You can always find the latest version of the library at 
  https://github.com/AndreiDegtiarev/ASensor

  This library is free software; you can redistribute it and/or
  modify it under the terms of the MIT license.
  Please see the included documents for further information.
*/
///Wrapper for DHT temperature and humidity sensor. To use this sensor https://github.com/markruys/arduino-DHT library has to be installed.
///Details to member functions see ISensor class documentation
class DHTTemperatureSensor : public ISensor
{
private:
#ifndef DEMO_SENSORS
	DHT *_dht;
#endif
	float _last_temperature;
	float _last_humidity;
	bool _isOK;
public:
	DHTTemperatureSensor(int port)
	{
#ifndef DEMO_SENSORS
		_dht=new DHT();
		_dht->setup(port);
#endif
		_last_humidity=0;
		_isOK=false;
	}

public:
	virtual const __FlashStringHelper* Name()
	{
		return F("DHT Temperature");
	}
	virtual float LowMeasurementLimit()
	{
		return -50;
	}
	virtual float HighMeasurementLimit()
	{
		return 50;
	}
	virtual int Precission()
	{
		return 1;
	}
	float LastHumidity()
	{
		return _last_humidity;
	}
	bool IsOK()
	{
		return _isOK;
	}
	virtual bool Measure(float &data)
	{
		_isOK=false;
#ifdef DEMO_SENSORS
		data =(float)rand()/RAND_MAX*5+20;
		_last_humidity = (float)rand()/RAND_MAX*10+60;
		_isOK=true;
#else
		DHT::DHT_ERROR_t status= DHT::ERROR_NONE;
		if(_dht!=NULL)
		{
			data = _dht->getTemperature();
			_last_humidity = _dht->getHumidity();
			status=_dht->getStatus();
		}
		/*Serial.print("Status: ");
		Serial.print(_dht->getStatusString());
		Serial.print(" Tempr: ");
		Serial.print(_last_temperature);
		Serial.print(" Humidity: ");
		Serial.println(_last_humidity);*/
		_isOK=status == DHT::ERROR_NONE && !isnan(_last_temperature) && !isnan(_last_humidity);
		//delay(_dht->getMinimumSamplingPeriod()); 
#endif
		return _isOK;
	}
};
