/* * =========================================================================
 * DOCUMENTATION
 * * Micro-controller: ESP32 (e.g., DevKit V1)
 * * Libraries Used:
 * 1. Adafruit_BNO08x.h (Library for BNO08x IMU)
 * Author: Adafruit
 * Link: https://github.com/adafruit/Adafruit_BNO08x
 * 2. Adafruit_Sensor.h (Adafruit Unified Sensor Driver)
 * Author: Adafruit
 * Link: https://github.com/adafruit/Adafruit_Sensor
 * =========================================================================
 */

#include <Adafruit_BNO08x.h>

// For I2C, define the reset pin. If not connected to a digital pin, set to -1
#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial monitor to open

  Serial.println("Adafruit BNO08x test!");

  // Initialize the sensor using I2C communication
  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");

  // Enable the Rotation Vector report (most common for 9-DOF orientation)
  if (!bno08x.enableReport(SH2_ROTATION_VECTOR)) {
    Serial.println("Could not enable rotation vector");
  }

  delay(100);
}

void loop() {
  // Check if the sensor has undergone a hardware reset
  if (bno08x.wasReset()) {
    Serial.print("Sensor was reset ");
    if (!bno08x.enableReport(SH2_ROTATION_VECTOR)) {
      Serial.println("Could not enable rotation vector");
    }
  }
  
  // Exit loop if no new sensor events are available
  if (!bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  
  switch (sensorValue.sensorId) {
    case SH2_ROTATION_VECTOR:
      // Extract Quaternion components (i, j, k, real)
      float x = sensorValue.un.rotationVector.i;
      float y = sensorValue.un.rotationVector.j;
      float z = sensorValue.un.rotationVector.k;
      float r = sensorValue.un.rotationVector.real;

      // Convert Quaternions to Euler angles (Heading, Pitch, Roll)
      // Heading (Yaw): Rotation around Z-axis
      float heading = atan2(2.0 * (x * y + r * z), 1.0 - 2.0 * (y * y + z * z)) * 180.0 / PI;
      // Pitch: Rotation around Y-axis
      float pitch = asin(2.0 * (x * z - r * y)) * 180.0 / PI;
      // Roll: Rotation around X-axis
      float roll = atan2(2.0 * (r * x + y * z), 1.0 - 2.0 * (x * x + y * y)) * 180.0 / PI;

      Serial.print("H: "); Serial.print(heading, 2);
      Serial.print(" P: "); Serial.print(pitch, 2);
      Serial.print(" R: "); Serial.println(roll, 2);
      break;
  }
  delay(50);
}