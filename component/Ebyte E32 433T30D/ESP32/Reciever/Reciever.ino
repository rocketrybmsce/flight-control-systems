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

void setup() {
  // USB Serial for debugging via Serial Monitor
  Serial.begin(115200);
  
  // Hardware Serial 2 for E32 (RX=16, TX=17)
  // Ensure the baud rate matches the Transmitter (9600 is default)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  Serial.println("Receiver Waiting for Data...");
}

void loop() {
  // Check if data has been received over the air by the E32 module
  if (Serial2.available()) {
    // Read the incoming string until a newline character is detected
    String incomingData = Serial2.readStringUntil('\n');
    
    // Print the received message to the local Serial Monitor
    Serial.print("Received: ");
    Serial.println(incomingData);
  }
}