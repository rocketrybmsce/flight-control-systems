/* * =========================================================================
 * DOCUMENTATION
 * * Micro-controller: ESP32 (e.g., DevKit V1)
 * * Libraries Used:
 * 1. Wire.h (Built-in Arduino I2C library)
 * 2. Adafruit_Sensor.h (Adafruit Unified Sensor Driver)
 * Author: Adafruit
 * Link: https://github.com/adafruit/Adafruit_Sensor
 * 3. Adafruit_BMP3XX.h (Library for BMP3XX sensors)
 * Author: Adafruit
 * Link: https://github.com/adafruit/Adafruit_BMP3XX
 * =========================================================================
 */

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BMP3XX.h"

// Standard sea level pressure is 1013.25 hPa. 
// For accurate altitude, update this with your local weather data.
#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP3XX bmp;

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println("BMP390 test");

  // Initialize the sensor via I2C (Address 0x77)
  if (!bmp.begin_I2C(0x77)) {   
    Serial.println("Could not find a valid BMP390 sensor, check wiring!");
    while (1);
  }

  // Configure sensor for high precision
  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ);
}

void loop() {
  if (!bmp.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  Serial.print("Temperature = ");
  Serial.print(bmp.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bmp.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bmp.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println("-----------------------");
  delay(2000);
}