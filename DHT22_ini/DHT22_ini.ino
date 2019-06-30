#include "DHTesp.h"
 
DHTesp dht;
 
void setup()
{
  Serial.begin(115200);
 
  dht.setup(4, DHTesp::DHT22);
}
 
void loop()
{
  float temperature = dht.getTemperature();
 
  Serial.print("Temperature: ");
  Serial.println(temperature);
 
  delay(1000);
 
}
