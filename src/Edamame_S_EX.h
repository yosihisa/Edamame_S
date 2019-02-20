#ifndef _Edamame_S_EX_h
#define _Edamame_S_EX_h

#include <Arduino.h>
#include <Wire.h>


#define INA226_ADDR 0x45
#define MOTOR_RF  13
#define MOTOR_RR  12
#define MOTOR_LF  14
#define MOTOR_LR  15
#define NICHROME  3
#define FLIGHT_PIN 0

void set_pinMode();

void motor(int ,int);
void nichrome(int);

void ina226_init();
long ina226_voltage();
long ina226_current();

#endif