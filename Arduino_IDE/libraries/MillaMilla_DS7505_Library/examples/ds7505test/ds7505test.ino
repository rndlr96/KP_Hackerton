/**************************************************************************/
/*!
This is a demo for the DS7505
----> https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS7505.html

This code derived from the Adafruit_MCP9808_Library.

Adafruit invests time and resources providing this open source code,
please support Adafruit and open-source hardware by purchasing
products from Adafruit!
*/
/**************************************************************************/

#include <Wire.h>
#include "MillaMilla_DS7505.h"

// Create the DS7505 temperature sensor object
MillaMilla_DS7505 tempsensor = MillaMilla_DS7505();

void setup() {
  delay(2000); // helpful on Teensy debugging to give time to open the serial monitor
  Serial.begin(9600);
  Serial.println("DS7505 demo");
  
  // Make sure the sensor is found, you can also pass in a different i2c
  // address with tempsensor.begin(0x48) for example
  if (!tempsensor.begin()) {
    Serial.println("Couldn't find DS7505!");
    while (1);
  }
}

void loop() {
  //Serial.println("wake up DS7505.... "); // wake up DS7505 for normal power use
  //tempsensor.wake();   // wake up, ready to read!  If you don't wake when shutdown, you still get a temp reading, it will be the last reading while awake.

  //tempsensor.write8(DS7505_REG_CONFIG, DS7505_REG_CONFIG_CONVRESOL_12_BITS); // change default precision from default of 9 bits

  // Read and print out the temperature, then convert to *F
  float c = tempsensor.readTempC();
  float f = c * 9.0 / 5.0 + 32;
  Serial.print("Temp: "); Serial.print(c); Serial.print("*C\t"); 
  Serial.print(f); Serial.println("*F");
  
  //Serial.println("Shutdown DS7505.... ");
  //tempsensor.shutdown(); // shutdown DS7505 for low power
  
  delay(1000);
}
