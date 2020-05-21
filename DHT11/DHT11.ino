#include "DHT.h"

DHT11 dht(1);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(1500);
  dht.read();
//  uint8_t *ptr = dht.getBuff();
//  Serial.println("Buffer:");
//  for(int i = 0; i < 5; i++) {
//    Serial.println(*ptr);
//    ptr++;
//  }
//  Serial.println("End buffer");
  
  Serial.print("Temp (°C): ");
  Serial.println(dht.getTempC());
  Serial.print("Temp (°F): ");
  Serial.println(dht.getTempF());
  Serial.print("Humidity: ");
  Serial.println(dht.getHumid());
  Serial.print("Parity byte: ");
  Serial.println(dht.getParity());
}
