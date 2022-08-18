#include <dht.h>

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

/**
 * TODO: This value determines the amount of time to wait in between measurements,
 * however, it can be done better.
 * Eventually I need to change this to where the python script requests the data,
 * rather than it constantly reading and producing measurements.
 */
// Amount of time for each half-blink, in milliseconds
#define BLINK_TIME 1000

#define DHT11_PIN 7
dht DHT;

int sensorPin1 = A0;
float sensorVal1 = 0;
float maxVal1 = 0;
float minVal1 = 1023;

int sensorPin2 = A1;
float sensorVal2 = 0;
float maxVal2 = 0;
float minVal2 = 1023;

int chk;

void setup() { Serial.begin(115200); }

void loop() {
  sensorVal1 = analogRead(sensorPin1);
  if (sensorVal1 > maxVal1) { maxVal1 = sensorVal1; }
  if (sensorVal1 < minVal1) { minVal1 = sensorVal1; }
//  float s1 = (sensorVal1 - minVal1)/(maxVal1 - minVal1);
  
  sensorVal2 = analogRead(sensorPin2);
  if (sensorVal2 > maxVal2) { maxVal2 = sensorVal2; }
  if (sensorVal2 < minVal2) { minVal2 = sensorVal2; }
//  float s2 = (sensorVal2 - minVal2)/(maxVal2 - minVal2);

  chk = DHT.read11(DHT11_PIN);
  debug("Temperature:");
  debug(DHT.temperature);
  debug(",Humidity:");
  debug(DHT.humidity);
  debug(",Photo:");
  debug(sensorVal1);
  debug(",Moisture:");
  debugln(sensorVal2);

  delay(BLINK_TIME);
}
