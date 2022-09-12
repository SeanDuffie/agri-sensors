#include <dht.h>

#define DHT11_PIN 7
dht DHT;
int LIGHT_PIN = A0; // LIGHT SENSOR
float LIGHT_VAL = 0;
int SOIL_PIN = A1; // SOIL SENSOR
float SOIL_VAL = 0;

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

void setup() { Serial.begin(115200); }

void loop() {
  if (Serial.available()) {
    String measureReq = "";
    measureReq = Serial.read();
    if (measureReq.equals("49")) {      // 49 is the ascii value for '1'
      LIGHT_VAL = analogRead(LIGHT_PIN);
      SOIL_VAL = analogRead(SOIL_PIN);
    
      int chk = DHT.read11(DHT11_PIN);
      debug(LIGHT_VAL);
      debug(",");
      debug(SOIL_VAL);
      debug(",");
      debug(DHT.temperature);
      debug(",");
      debug(DHT.humidity); // debugln??
    } else if (measureReq.equals("10")) { // Do nothing, this is a return character
    } else {
      debug("Invalid Request: ");
      debugln(measureReq);
    }
  } else {}
}
