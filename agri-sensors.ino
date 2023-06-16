/*
 * This Program is an example for how to initialize a device with a WiFi connection
 * The device will start up and look for any existing credentials from previous connections
 * If none are found and successfully connected, a wireless AP will be created for configuration
 */
#include <WiFiManager.h>
#include <WiFi.h>
// #include <dht.h>
// #include <Adafruit_BME280.h>

// #define DHT11_PIN 33
// dht DHT;
#define LIGHT_PIN 5     // LIGHT SENSOR
float LIGHT_VAL = 0;
#define SOIL_PIN 32     // SOIL SENSOR
float SOIL_VAL = 0;
#define SPEAKER 25      // SPEAKER OUTPUT
#define WATER_PUMP 33   // WATER PUMP OUTPUT

#define DEBUG 1
#if DEBUG == 1
#define debug(x) Serial.print(x)
#define debugln(x) Serial.println(x)
#else
#define debug(x)
#define debugln(x)
#endif

WiFiManager wm;

WiFiServer server(80); // Create an instance of the wifiserver on port 80

void setup() {
    Serial.begin(115200);
    // #ifndef WIFI_MODE_STA
    // #define WIFI_MODE_STA 2
    // #endif
    WiFi.mode(WIFI_AP_STA); // explicitly set mode, esp defaults to STA+AP

    debugln("\n================================");
    debugln("** Starting Synthetic Garden...");
    debug("** Device MAC Address: ");
    debugln(WiFi.macAddress());

    /************************************  Start WiFi Manager  *************************************/
    wm.setDebugOutput(false);                 // Comment out to enable Debug
    wm.setAPCallback(configModeCallback);     // Callback Function to Config Mode
    // Set Static IP and Config Portal IP Addresses manually
    wm.setSTAStaticIPConfig(IPAddress(192,168,0,177), IPAddress(192,168,0,1), IPAddress(255,255,255,0));
    wm.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));
    
    wm.setConfigPortalTimeout(120);           // How long to wait in Config Mode
    wm.setConnectTimeout(20);                 // How long to try to connect
    wm.setClass("invert");                    // Dark Theme for config mode
    
    if (!wm.autoConnect("AutoConnectAP")) {   // Handles AutoConnect Failures
        debugln("** Failed to connect or hit timeout");
        debugln("** Restarting in 3 seconds...");
        debugln("================================");
        delay(3000);
        ESP.restart();
    }
    /************************************   End WiFi Manager   *************************************/

    /************************************   Start Pin Setup    *************************************/
    // Set input pins
    pinMode(LIGHT_PIN, INPUT);
    pinMode(SOIL_PIN, INPUT);
    // Set output pins
    pinMode(SPEAKER, OUTPUT);
    pinMode(WATER_PUMP, OUTPUT);
    // Set outputs to LOW
    digitalWrite(SPEAKER, LOW);
    digitalWrite(WATER_PUMP, LOW);
    /************************************    End Pin Setup     *************************************/

    server.begin(); // Start the server
    debug("** Local IP: ");
    debugln(WiFi.localIP());    // Print the IP address
    debugln("** Setup Complete!");
    debugln("================================");
}

void loop() {
    LIGHT_VAL = analogRead(LIGHT_PIN);
    SOIL_VAL = analogRead(SOIL_PIN);

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

// Config Mode Function, Starts AP for configuring 
void configModeCallback(WiFiManager *myWiFiManager) {
  /*
  * This Function is called whenever no existing connection is found
  * 
  */
  debugln("*** Entered config mode");
  
//  debug("*** AP IP: ");
//  debugln(WiFi.softAPIP());

  debug("*** AP SSID: ");
  debugln(myWiFiManager->getConfigPortalSSID());
}
