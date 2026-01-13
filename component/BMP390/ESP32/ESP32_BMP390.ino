#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME380.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME380 bme; // I2C

void setup() {
  Serial.begin(115200);
  while (!Serial);
  Serial.println(F("BME390 Test"));

  // Initialize the sensor using I2C (Address is usually 0x77 or 0x76)
  if (!bme.begin_I2C(0x77)) {   // If it fails, try 0x76
    Serial.println("Could not find a valid BME390 sensor, check wiring!");
    while (1);
  }

  // Set up oversampling and filter configurations
  bme.setTemperatureOversampling(BME380_OVERSAMPLING_8X);
  bme.setPressureOversampling(BME380_OVERSAMPLING_64X);
  bme.setIIRFilterCoeff(BME380_FILTER_COEFF_3);
  bme.setOutputDataRate(BME380_ODR_12_5_HZ);
}

void loop() {
  if (! bme.performReading()) {
    Serial.println("Failed to perform reading :(");
    return;
  }

  Serial.print("Temperature = ");
  Serial.print(bme.temperature);
  Serial.println(" *C");

  Serial.print("Pressure = ");
  Serial.print(bme.pressure / 100.0);
  Serial.println(" hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println(" m");

  Serial.println();
  delay(2000);
}