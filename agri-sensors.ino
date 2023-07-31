#include <dht.h>

#define DHT11_PIN 7
dht DHT;
#define LIGHT_PIN A0 // LIGHT SENSOR
#define SOIL_PIN A1 // SOIL SENSOR
#define SPEAKER 2     // SPEAKER OUTPUT
#define WATER_PUMP 4  // WATER PUMP OUTPUT

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

void setup() {
  Serial.begin(115200);
  pinMode(SPEAKER, OUTPUT);
  pinMode(WATER_PUMP, OUTPUT);
}

void loop() {
    int LIGHT_VAL = analogRead(LIGHT_PIN);
    int SOIL_VAL = analogRead(SOIL_PIN);

    // int chk = DHT.read11(DHT11_PIN);

    // Debug values
    debug("Current Light = ");
    debugln(LIGHT_VAL);
    // debug(",");
    debug("Current Soil = ");
    debugln(SOIL_VAL);
    // if (chk) {
    //     // debug(",");
    //     debug("Current Temp = ");
    //     debugln(DHT.temperature);
    //     // debug(",");
    //     debug("Current Humidity = ");
    //     debugln(DHT.humidity);
    // }
    // debugln();

    // If dry, sound buzzer and activate pump for a time
    if (SOIL_VAL < 256) {
        digitalWrite(WATER_PUMP, HIGH);
        int c = 0;
        while (c < 3) {
            digitalWrite(SPEAKER, HIGH);
            delay(100);
            digitalWrite(SPEAKER, LOW);
            delay(100);
            c++;
        }
        delay(4400);
        digitalWrite(WATER_PUMP, LOW);
    }

    // Measurement interval
    delay(5000);
}
