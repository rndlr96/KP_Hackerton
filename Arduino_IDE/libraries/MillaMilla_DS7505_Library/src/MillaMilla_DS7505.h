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

#ifndef _MILLAMILLA_DS7505_H
#define _MILLAMILLA_DS7505_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <Wire.h>


#define DS7505_I2CADDR_DEFAULT                0x48
#define DS7505_REG_TEMP                       0x00

#define DS7505_REG_CONFIG                     0x01
#define DS7505_REG_CONFIG_NVMEMSTATUS         0x80
#define DS7505_REG_CONFIG_CONVRESOL1          0x40
#define DS7505_REG_CONFIG_CONVRESOL0          0x20
#define DS7505_REG_CONFIG_THRMFLTTOL1         0x10
#define DS7505_REG_CONFIG_THRMFLTTOL0         0x08
#define DS7505_REG_CONFIG_THRMOUTPOL          0x04
#define DS7505_REG_CONFIG_THRMOPMODE          0x02
#define DS7505_REG_CONFIG_SHUTDOWN            0x01
#define DS7505_REG_CONFIG_CONVRESOL_09_BITS   0x00
#define DS7505_REG_CONFIG_CONVRESOL_10_BITS   0x20
#define DS7505_REG_CONFIG_CONVRESOL_11_BITS   0x40
#define DS7505_REG_CONFIG_CONVRESOL_12_BITS   0x60
#define DS7505_REG_CONFIG_CONVRESOL_ALL_BITS  0x60

#define DS7505_REG_THYST                      0x02
#define DS7505_REG_TOS                        0x03

class MillaMilla_DS7505 {
 public:
  MillaMilla_DS7505();
  boolean begin(uint8_t a = DS7505_I2CADDR_DEFAULT);  
  float readTempF( void );
  float readTempC( void );
  void shutdown_wake( uint8_t sw_ID );
  void shutdown(void);
  void wake(void);

  void write8(uint8_t reg, uint8_t val);
  uint16_t read16(uint8_t reg);
  uint8_t read8(uint8_t reg);

 private:
  uint8_t _i2caddr;
};

#endif
