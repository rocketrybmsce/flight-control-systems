#include <Adafruit_BNO08x.h>

// For I2C, we define the reset pin. If not connected, set to -1
#define BNO08X_RESET -1

Adafruit_BNO08x  bno08x(BNO08X_RESET);
sh2_SensorValue_t sensorValue;

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10); // Wait for serial monitor

  Serial.println("Adafruit BNO08x test!");

  // Try to initialize!
  if (!bno08x.begin_I2C()) {
    Serial.println("Failed to find BNO08x chip");
    while (1) { delay(10); }
  }
  Serial.println("BNO08x Found!");

  // Enable the Rotation Vector report
  if (!bno08x.enableReport(SH2_ROTATION_VECTOR)) {
    Serial.println("Could not enable rotation vector");
  }

  delay(100);
}

void loop() {
  if (bno08x.wasReset()) {
    Serial.print("sensor was reset ");
    if (!bno08x.enableReport(SH2_ROTATION_VECTOR)) {
      Serial.println("Could not enable rotation vector");
    }
  }
  
  if (!bno08x.getSensorEvent(&sensorValue)) {
    return;
  }
  
  switch (sensorValue.sensorId) {
    case SH2_ROTATION_VECTOR:
      // Convert quaternion to Euler angles (Heading, Pitch, Roll)
      float x = sensorValue.un.rotationVector.i;
      float y = sensorValue.un.rotationVector.j;
      float z = sensorValue.un.rotationVector.k;
      float r = sensorValue.un.rotationVector.real;

      // Basic conversion to degrees
      float heading = atan2(2.0 * (x * y + r * z), 1.0 - 2.0 * (y * y + z * z)) * 180.0 / PI;
      float pitch = asin(2.0 * (x * z - r * y)) * 180.0 / PI;
      float roll = atan2(2.0 * (r * x + y * z), 1.0 - 2.0 * (x * x + y * y)) * 180.0 / PI;

      Serial.print("H: "); Serial.print(heading, 2);
      Serial.print(" P: "); Serial.print(pitch, 2);
      Serial.print(" R: "); Serial.println(roll, 2);
      break;
  }
  delay(50);
}