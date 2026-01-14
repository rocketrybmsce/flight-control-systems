#include <Arduino.h>

int count = 0;

void setup() {
  // USB Serial for debugging
  Serial.begin(115200);
  
  // Hardware Serial 2 for E32 (RX=16, TX=17)
  // Baud rate 9600 is the factory default for E32
  Serial2.begin(9600, SERIAL_8N1, 16, 17);
  
  Serial.println("Transmitter Initialized...");
}

void loop() {
  Serial.print("Sending: ");
  Serial.println(count);

  // Send the count as a string followed by a newline
  Serial2.println(count);

  count++;
  delay(2000); 
}