#ifndef _RTC
#define _RTC

#include <Arduino.h>
#include <Wire.h>
#include <stdint.h>

class RTC1307 {
    public:
        RTC1307(uint8_t addr);
        int sync_time(void);
        uint8_t getHour(void);

    private:
        uint8_t address;
        uint8_t hours;
};

#endif
