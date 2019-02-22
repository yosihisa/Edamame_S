#ifndef _Edamame_S_EX_h
#define _Edamame_S_EX_h

#include <Arduino.h>
#include <Wire.h>
#include "Edamame_S.h"


#define INA226_ADDR 0x45
#define MOTOR_RF  12
#define MOTOR_RR  13
#define MOTOR_LF  15
#define MOTOR_LR  14
#define NICHROME  3
#define FLIGHT_PIN 0

struct control_data {
	String log_path = "";
	long log_num = 0;
	int mode = 0;
	int flightPin = 0;

	long voltage = 0;
	long current = 0;

	struct gps gps_data;
	struct xyza LSM303_data;

	float arg = 0;

	int  motor_L = 0, motor_R = 0, nichrome = 0;

};

void set_pinMode();

void motor(int ,int);
void nichrome(int);

void ina226_init();
long ina226_voltage();
long ina226_current();

void print_data(control_data *data);
void write_data(control_data *data);


#endif