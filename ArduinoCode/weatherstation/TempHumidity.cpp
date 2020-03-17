#include "TempHumidity.h"

TempHumidity::TempHumidity(int data_pin0, int data_pin1, bool parity_check) {
    m_data_pin0 = data_pin0;
    m_data_pin1 = data_pin1;
    m_parity_check = parity_check;

    m_cur_temp = -1;
    m_cur_humidity = -1;

    pinMode(m_data_pin0, OUTPUT);
    pinMode(m_data_pin1, INPUT);
}

//convenience getter methods just in case
int TempHumidity::getDataPin0(void) {
    return m_data_pin0;
}

int TempHumidity::getDataPin1(void) {
    return m_data_pin1;
}

bool TempHumidity::isParityChecking(void) {
    return m_parity_check;
}

int TempHumidity::getHumidityRH(void) {
    return m_cur_humidity;
}

int TempHumidity::getTempC(void) {
    return m_cur_temp;
}

int TempHumidity::getTempF(void) {
    return (int)(((double) m_cur_temp * (9.0/5.0)) + 32.0);
}

/* updates the temp and humidity values by polling the sensor
*  returns 0 if it fails, 1 otherwise*/
int TempHumidity::update(void) {
    pinMode(m_data_pin1, OUTPUT);
    digitalWrite(m_data_pin1, LOW);
    delay(20);
//    digitalWrite(m_data_pin0, HIGH);
    pinMode(m_data_pin1, INPUT);
    long long raw_data = 0;
    for(int i = 0; i < 32; i++) {
        //wait until the data pin is pulled low 
        while(digitalRead(m_data_pin1));
        long start_time = micros();
        //wait until pin returns to high
        while(!digitalRead(m_data_pin1));
        long dif = micros() - start_time;
        //if the update is called during a wrap around of the microsecond counter, exit and return an error
        if(dif < 0) return 0;
        raw_data <<= 1;
        raw_data += dif > 60 ? 1 : 0;
    }
    //TODO implement parity checking
    int parity = raw_data & 0xFF;
    int temp_humidity = raw_data & 0xFF00000000;
    int temp_temp = raw_data & 0xFF000000;
    m_cur_humidity = temp_humidity;
    m_cur_temp = temp_temp;
    Serial.println((long) raw_data);
    return 1;
}
