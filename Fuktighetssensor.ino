//Blynk definisjoner
#define BLYNK_PRINT Serial
#include <ESP8266_Lib.h>
#include <BlynkSimpleShieldEsp8266.h>

// You should get Auth Token in the Blynk App.
char auth[] = "n-6M_g30TddX8H026HvuegCQ2cXuRssg";
char ssid[] = "AirTies_Air4920_3N8C"; //You can replace the wifi name to your wifi
char pass[] = "fyphcd8797";  //Type password of your wifi.

#include <SoftwareSerial.h>
SoftwareSerial EspSerial(3, 2); // RX, TX
// Your ESP8266 baud rate:
#define ESP8266_BAUD 9600
ESP8266 wifi(&EspSerial);

#include "cactus_io_DHT22.h"

#define DHT22_PIN 4     // what pin on the arduino is the DHT22 data line connected to

// For details on how to hookup the DHT22 sensor to the Arduino then checkout this page
// http://cactus.io/hookups/sensors/temperature-humidity/dht22/hookup-arduino-to-dht22-temp-humidity-sensor

// Initialize DHT sensor for normal 16mhz Arduino.
DHT22 dht(DHT22_PIN);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  // Set ESP8266 baud rate
  EspSerial.begin(ESP8266_BAUD);
  delay(10);

  Blynk.begin(auth, wifi, ssid, pass);

}

BLYNK_READ(V0) //Blynk app has something on V5
{
  //Read data and store it to variables hum and temp
  dht.readHumidity();
  dht.readTemperature();
  /*Serial.print("Humidity: ");
  Serial.print(dht.humidity);
  Serial.print(" %, Temp: ");
  Serial.print(dht.temperature_C);
  Serial.println(" Celsius");
  delay(2000); //Delay 2 sec.*/
  String data = "Hum: " + String(dht.humidity) + "%                    Temp: " + String(dht.temperature_C) + "*C";
  Blynk.virtualWrite(V0, data); //sending to Blynk
}


void loop()
{
  Blynk.run();
}
