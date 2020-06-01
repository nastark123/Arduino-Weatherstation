#include "RTC.h"

RTC1307::RTC1307(uint8_t addr) {
    //addr will be 0x68 for the DS1307    
    Wire.begin();
    address = addr;
    hours = 0;
}

int RTC1307::sync_time(void) {
    Wire.beginTransmission(address);
    Wire.write(0x02);
    Wire.requestFrom(address, 1);
    if(Wire.available()) {
        hours = Wire.read();
    }
    Wire.endTransmission();
}

uint8_t RTC1307::getHour(void) {
  return hours;
}
