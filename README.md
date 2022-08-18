# agri-sensors

## Purpose

This is the Arduino code for reading in sensor data from my plants that I monitor

## How it works

The only dependency is the is the "dht.h" library that was installed through the Arduino IDE.
3 different analog signals are read through different pins of the Arduino. The first is a pull down resistor that's connected to pin A0 and a photoresistor. The second is a capacitive soil moisture sensor connected to pin A1. Finally the third is a DHT11 temperature and humidity sensor connected to digital pin 7, this can be queried in the code to either read the temperature in celsius or the humidity in percentage.

## TODO

- Configure the output to be transmitted properly over a serial connection to python code
- Replace the delay with a query so that the python can request a reading/output whenever required
