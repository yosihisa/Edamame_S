#ifndef _Edamame_S_h
#define _Edamame_S_h

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>

#define LSM303AGR_A 0x19
#define LSM303AGR_M 0x1E
#define SD_CS       4
#define LED0        18
#define LED1        19
#define Serial_PC   Serial
#define Serial_GPS  Serial1

struct xyza {
    int16_t x,y,z;
    int16_t x_offset=0;
    int16_t y_offset=0;
    int16_t z_offset=0;
    float arg;
};

struct gps {
	long latitude;
	long longitude;
	uint8_t hh, mm, ss;
	uint16_t ms;

	int mode = 0;

	float arg = 0;
	unsigned long dist = 0;
};


void LSM303_init_m();
void LSM303_update_m(struct xyza *data);

void set_gpsHiSpeed();
long get_gps(struct gps *gps_data , unsigned long t);
void calc_gps(struct gps *gps_data, long latitude, long longitude);

#endif