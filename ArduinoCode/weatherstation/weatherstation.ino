#include "TempHumidity.h"

TempHumidity temp_humidity(2, 3, false);

void setup() {
  Serial.begin(9600);
}

void loop() {
  temp_humidity.update();
//  Serial.println(temp_humidity.getHumidityRH());
//  Serial.println(temp_humidity.getTempF());
  delay(5000);
}
