/* * =========================================================================
 * DOCUMENTATION
 * * Micro-controller: ESP32 (e.g., DevKit V1)
 * * Libraries Used:
 * 1. TinyGPS++.h (GPS data parsing library)
 * Author: Mikal Hart
 * Link: https://github.com/mikalhart/TinyGPSPlus
 * 2. HardwareSerial.h (Built-in ESP32 Serial library)
 * Author: Espressif Systems
 * =========================================================================
 */

#include <TinyGPS++.h>
#include <HardwareSerial.h>

// The TinyGPS++ object handles the parsing of NMEA sentences
TinyGPSPlus gps;

// Using ESP32 Hardware Serial Port 2 (UART2)
// Default pins for RX2/TX2 are GPIO 16 and 17
HardwareSerial SerialGPS(2);

void setup() {
  // Serial monitor for debugging at 115200 baud
  Serial.begin(115200);
  
  // GPS module communication (Standard baud rate is 9600)
  // Pin mapping: RX=16 (connected to GPS TX), TX=17 (connected to GPS RX)
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);

  Serial.println("ESP32 GPS Initializing...");
}

void loop() {
  // Feed characters from the GPS module into the TinyGPS++ object
  while (SerialGPS.available() > 0) {
    if (gps.encode(SerialGPS.read())) {
      displayInfo();
    }
  }

  // Error handling: Check for wiring issues if no data is received within 5 seconds
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    Serial.println("No GPS data received: check wiring or outdoor view");
    delay(2000);
  }
}

// Function to print parsed GPS data to the Serial Monitor
void displayInfo() {
  Serial.print("Location: "); 
  if (gps.location.isValid()) {
    Serial.print(gps.location.lat(), 6);
    Serial.print(",");
    Serial.print(gps.location.lng(), 6);
  } else {
    Serial.print("INVALID (Wait for Satellite Fix)");
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
    // Formatting time with leading zeros for readability
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