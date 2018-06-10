#include "DHT.h"
#include <DebugSerial.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  DebugSerial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
  int h = dht.readHumidity();
  int t = dht.readTemperature();

  DebugSerial.print("Humidity: ");
  DebugSerial.print(h);
  DebugSerial.print("%\t");
  DebugSerial.print("Temperature: ");
  DebugSerial.print(t);
  DebugSerial.print(" C");
}
