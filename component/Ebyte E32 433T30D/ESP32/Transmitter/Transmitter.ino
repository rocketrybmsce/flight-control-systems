/* * =========================================================================
 * DOCUMENTATION
 * * Micro-controller: ESP32 (e.g., DevKit V1)
 * * Libraries Used:
 * 1. Arduino.h (Standard Arduino base library)
 * 2. HardwareSerial.h (Built-in ESP32 serial communication)
 * Author: Espressif Systems
 * * Note: This code uses raw Serial2 communication for the EBYTE E32 LoRa 
 * module. No external library zip is required for this basic implementation.
 * =========================================================================
 */

#include <Arduino.h>

int count = 0;

void setup() {
  // USB Serial for debugging via Serial Monitor
  Serial.begin(115200);
  
  // Hardware Serial 2 for E32 (RX=16, TX=17)
  // Baud rate 9600 is the factory default for EBYTE E32 modules
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  Serial.println("Transmitter Initialized...");
}

void loop() {
  // Display the current count on the local Serial Monitor
  Serial.print("Sending: ");
  Serial.println(count);

  // Transmit the count over the air via E32 LoRa module
  // Sent as a string followed by a newline for easy parsing on the receiver
  Serial2.println(count);

  count++;
  
  // Delay of 2 seconds between transmissions to avoid flooding the frequency
  delay(2000); 
}