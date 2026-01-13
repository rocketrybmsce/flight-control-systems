#include <TinyGPS++.h>
#include <HardwareSerial.h>

// The TinyGPS++ object
TinyGPSPlus gps;

// Use HardwareSerial port 2
// RX = GPIO 16, TX = GPIO 17
HardwareSerial SerialGPS(2);

void setup() {
  // Debug console
  Serial.begin(115200);
  
  // GPS baud rate is usually 9600
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 GPS Initializing...");
}

void loop() {
  // Read data from GPS module
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      displayInfo();
    }
  }

  // If 5 seconds pass and no characters arrive, check wiring
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: check wiring");
    delay(2000);
  }
}

void displayInfo() {
  Serial.print("Location: "); 
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print("INVALID");
  }

  Serial.print("  Date/Time: ");
  if (gps.date.isValid()) {
    Serial.print(gps.date.month());
    Serial.print("/");
    Serial.print(gps.date.day());
    Serial.print("/");
    Serial.print(gps.date.year());
  } else {
    Serial.print("INVALID");
  }

  Serial.print(" ");
  if (gps.time.isValid()) {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(":");
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(":");
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
  } else {
    Serial.print("INVALID");
  }

  Serial.println();
}