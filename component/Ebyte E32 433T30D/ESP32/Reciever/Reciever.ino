#include <Arduino.h>

void setup() {
  // USB Serial for debugging
  Serial.begin(115200);
  
  // Hardware Serial 2 for E32 (RX=16, TX=17)
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  Serial.println("Receiver Waiting for Data...");
}

void loop() {
  if (Serial2.available()) {
    // Read the incoming string until a newline character
    String incomingData = Serial2.readStringUntil('\n');
    
    Serial.print("Received: ");
    Serial.println(incomingData);
  }
}