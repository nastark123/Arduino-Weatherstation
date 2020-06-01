#include "RTC.h"

RTC1307 rtc(0x68);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  rtc.sync_time();
  Serial.println(rtc.getHour());
}
