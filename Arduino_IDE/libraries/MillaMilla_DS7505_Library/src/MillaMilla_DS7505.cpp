/**************************************************************************/
/*! 
    @file     MillaMilla_DS7505.h
    @author   Brooke Hedrick (MillaMilla Enterprises)
	@license  BSD (see license.txt)
	
	This is a library for the Adafruit DS7505 Temp Sensor 
	----> https://www.maximintegrated.com/en/products/analog/sensors-and-sensor-interface/DS7505.html
	
	This code was originally derived from the Adafruit_MCP9808_Library.
	
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#ifdef __AVR_ATtiny85__
 #include "TinyWireM.h"
 #define Wire TinyWireM
#else
 #include <Wire.h>
#endif

#include "MillaMilla_DS7505.h"

/**************************************************************************/
/*! 
    @brief  Instantiates a new DS7505 class
*/
/**************************************************************************/
MillaMilla_DS7505::MillaMilla_DS7505() {
}

/**************************************************************************/
/*! 
    @brief  Setups the HW
*/
/**************************************************************************/
boolean MillaMilla_DS7505::begin(uint8_t addr) {
  _i2caddr = addr;
  Wire.begin();

  write8(DS7505_REG_CONFIG, 0x0);
  return true;
}
 
/**************************************************************************/
/*! 
    @brief  Reads the 16-bit temperature register and returns the Centigrade
            temperature as a float.

*/
/**************************************************************************/
float MillaMilla_DS7505::readTempC( void )
{
  uint8_t c = read8(DS7505_REG_CONFIG); // need this for the precision 
  uint16_t t = read16(DS7505_REG_TEMP);
  uint16_t t2 = (t & 0x7FFF); // 1st bit is the sign

  float temp = 0.0;
  
  if ((c & DS7505_REG_CONFIG_CONVRESOL_ALL_BITS) == DS7505_REG_CONFIG_CONVRESOL_09_BITS) {
    t2 = t2 >> 7;
    temp = t2 / 2.0;
  } else if ((c & DS7505_REG_CONFIG_CONVRESOL_ALL_BITS) == DS7505_REG_CONFIG_CONVRESOL_10_BITS) {
    t2 = t2 >> 6;
    temp = t2 / 4.0;
  } else if ((c & DS7505_REG_CONFIG_CONVRESOL_ALL_BITS) == DS7505_REG_CONFIG_CONVRESOL_11_BITS) {
    t2 = t2 >> 5;
    temp = t2 / 8.0;
  } else { // 12 bits
    t2 = t2 >> 4; 
    temp = t2 / 16.0;
  }

  if ((t & 0x8000) == 0x8000) temp -= 128;

  return temp;
}



//*************************************************************************
// Set Sensor to Shutdown-State or wake up (Conf_Register BIT8)
// 1= shutdown / 0= wake up
//*************************************************************************

void MillaMilla_DS7505::shutdown_wake( uint8_t sw_ID )
{
    uint8_t conf_shutdown ;
    uint8_t conf_register = read16(DS7505_REG_CONFIG);
    if (sw_ID == 1)
    {
       conf_shutdown = conf_register | DS7505_REG_CONFIG_SHUTDOWN ;
       write8(DS7505_REG_CONFIG, conf_shutdown);
    }
    if (sw_ID == 0)
    {
       conf_shutdown = conf_register & ~DS7505_REG_CONFIG_SHUTDOWN ;
       write8(DS7505_REG_CONFIG, conf_shutdown);
    }
}

void MillaMilla_DS7505::shutdown(void)
{
  shutdown_wake(1);
}

void MillaMilla_DS7505::wake(void)
{
  shutdown_wake(0);
  delay(250);
}



/**************************************************************************/
/*! 
    @brief  Low level 8 and 16 bit read and write procedures!
*/
/**************************************************************************/

void MillaMilla_DS7505::write8(uint8_t reg, uint8_t value) {
    Wire.beginTransmission(_i2caddr);
    Wire.write((uint8_t)reg);
    Wire.write(value);
    Wire.endTransmission();
}

uint16_t MillaMilla_DS7505::read16(uint8_t reg) {
  uint16_t val;

  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)2);
  val = Wire.read();
  val <<= 8;
  val |= Wire.read();  
  return val;  
}

uint8_t MillaMilla_DS7505::read8(uint8_t reg) {
  uint16_t val;

  Wire.beginTransmission(_i2caddr);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();
  
  Wire.requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  val = Wire.read();
  return val;  
}
