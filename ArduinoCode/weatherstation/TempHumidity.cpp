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

/* updates the temp and humidity values by polling the sensor
*  returns 0 if it fails, 1 otherwise*/
int TempHumidity::update(void) {
    digitalWrite(m_data_pin0, LOW);
    delay(20);
    digitalWrite(m_data_pin0, HIGH);
}