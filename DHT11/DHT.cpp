#include "DHT.h"

DHT11::DHT11(int pin, int timeout_micros) {
    p = pin;
    t = timeout_micros;
}

int DHT11::read(void) {
    pinMode(p, OUTPUT);
    digitalWrite(p, LOW);
    delay(18);
    digitalWrite(p, HIGH);
    delayMicroseconds(40);
    pinMode(p, INPUT);
    
    //variable that is decremented until the sensor responds, if it hits 0, it will return a timeout error
    int timeout_start = micros();
    while(digitalRead(p) == LOW) {
        if(micros() - timeout_start > t) return -1;
    }

    timeout_start = micros();
    while(digitalRead(p) == HIGH) {
        if(micros() - timeout_start > t) return -1;
    }

    for(int i = 0; i < sizeof(buff)/sizeof(uint8_t); i++) {
        for(int j = 0; j < 8; j++) {
            timeout_start = micros();
            while(digitalRead(p) == LOW) {
                if(micros() - timeout_start > t) return -1;
            }
            
            int first_time = micros();

            timeout_start = micros();
            while(digitalRead(p) == HIGH) {
                if(micros() - timeout_start > t) return -1;
            }

            buff[i] <<= 1;
            buff[i] |= (micros() - first_time > 40) ? 1 : 0;
        }
    }

    if(buff[0] + buff[2] + buff[3] != buff[4]) return -1;

    temp = buff[2];
    humid = buff[0];

    return 0;
}

int DHT11::getTempC(void) {
    return temp;
}

int DHT11::getTempF(void) {
    return (int) ((double) temp * 9.0 / 5.0) + 32;
}

int DHT11::getHumid(void) {
  return humid;
}

int DHT11::getParity(void) {
  return buff[4];
}

uint8_t* DHT11::getBuff(void) {
  return buff;
}
