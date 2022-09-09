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
//#define BLINK_TIME 1000
String measureReq = "";

#define DHT11_PIN 7
dht DHT;

int LIGHT_PIN = A0; // LIGHT SENSOR
float LIGHT_VAL = 0;
float LIGHT_MAX = 0;
float LIGHT_MIN = 1023;

int SOIL_PIN = A1; // SOIL SENSOR
float SOIL_VAL = 0;
float SOIL_MAX = 0;
float SOIL_MIN = 1023;

int chk;

void setup() { Serial.begin(115200); }

void loop() {
  if (Serial.available()) {
    measureReq = Serial.read();
    if (measureReq.equals("49")) {      // 49 is the ascii value for '1'

      LIGHT_VAL = analogRead(LIGHT_PIN);
      if (LIGHT_VAL > LIGHT_MAX) { LIGHT_MAX = LIGHT_VAL; }
      if (LIGHT_VAL < LIGHT_MIN) { LIGHT_MIN = LIGHT_VAL; }
//      float W_LIGHT = (LIGHT_VAL - LIGHT_MIN)/(LIGHT_MAX - LIGHT_MIN);

      SOIL_VAL = analogRead(SOIL_PIN);
      if (SOIL_VAL > SOIL_MAX) { SOIL_MAX = SOIL_VAL; }
      if (SOIL_VAL < SOIL_MIN) { SOIL_MIN = SOIL_VAL; }
//      float W_SOIL = (SOIL_VAL - SOIL_MIN)/(SOIL_MAX - SOIL_MIN);
    
      chk = DHT.read11(DHT11_PIN);
      debug(LIGHT_VAL);
      debug(",");
      debug(SOIL_VAL);
      debug(",");
      debug(DHT.temperature);
      debug(",");
      debug(DHT.humidity);
    } else if (measureReq.equals("10")) { // Do nothing, this is a return character
    } else {
      debug("Invalid Request: ");
      debugln(measureReq);
    }
  } else {
//    debugln("Waiting...");
  }
//  delay(BLINK_TIME);
}
