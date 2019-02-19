#ifndef _Edamame_S_EX_h
#define _Edamame_S_EX_h

#include <Arduino.h>
#include <Wire.h>


#define INA226_ADDR 0x45
#define MOTOR_RF  12
#define MOTOR_RR  13
#define MOTOR_LF  15
#define MOTOR_LR  14
#define NICHROME  3
#define flightPin 0


void Motor(int ,int);
void Nichrome(int);
void ina226_init();
long ina226_voltage();
long ina226_current();

#endif