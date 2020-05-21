#ifndef DHT
#define DHT

#include <stdint.h>
#include <Arduino.h>

class DHT11 {
    public:
        DHT11(int pin, int timeout_micros = 1000);
        int read(void);
        int getTempC(void);
        int getTempF(void);
        int getHumid(void);
        int getParity(void);
        uint8_t* getBuff(void);
    private:
        int t;
        int p;
        int temp;
        int humid;
        uint8_t buff[5];
};

#endif
