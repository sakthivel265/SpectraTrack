#include <TinyGPS++.h>
#ifdef ESP32
#include <HardwareSerial.h>
HardwareSerial mygps(2);
#elif defined(ESP8266)
#include <SoftwareSerial.h>
SoftwareSerial mygps(D5, D6);
#elif defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
#include <SoftwareSerial.h>
SoftwareSerial mygps(4, 3);
#else
#error "Unsupported microcontroller! This code is for ESP32, ESP8266, ATmega328, or ATmega168."
#endif
TinyGPSPlus gps;

void setup() {
  Serial.begin(115200);
  mygps.begin(9600);
  delay(1000);
  Serial.println("\nGPS Testing");
}

void loop() {
  while (mygps.available() > 0) {
    if (gps.encode(mygps.read()) || gps.location.isUpdated()) {
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      Serial.print("\tLongitude= ");
      Serial.println(gps.location.lng(), 6);
      delay(1000);
    }
  }
}
