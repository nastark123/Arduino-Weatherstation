#ifndef temphumidity
#define temphumidity

#include <SPI.h>

class TempHumidity {
    public:
        TempHumidity(int data_pin0, int data_pin1, bool parity_check);
        int getDataPin0(void);
        int getDataPin1(void);
        bool isParityChecking(void);
        int getHumidityRH(void);
        int getTempC(void);
        int getTempF(void);
        int update(void);

    private:
        int m_data_pin0;
        int m_data_pin1;
        bool m_parity_check;
        int m_cur_temp;
        int m_cur_humidity;
};

#endif