#include "Edamame_S.h"
#include <string.h>

void LSM303_init_m() {
	Wire.beginTransmission(LSM303AGR_M);
	Wire.write(0x60);
	Wire.write(0b00001101);
	Wire.endTransmission(true);
	Wire.beginTransmission(LSM303AGR_M);
	Wire.write(0x61);
	Wire.write(0b00000100);
	Wire.endTransmission(true);
	Wire.beginTransmission(LSM303AGR_M);
	Wire.write(0x62);
	Wire.write(0b00010000);
	Wire.endTransmission(true);
}

void LSM303_update_m(struct xyza *data) {

	Wire.beginTransmission(LSM303AGR_M);
	Wire.write(0x60);
	Wire.write(0b00001101);
	Wire.endTransmission(true);

	Wire.beginTransmission(LSM303AGR_M);
	Wire.write(0x68);
	Wire.endTransmission(false);
	Wire.requestFrom((uint8_t)LSM303AGR_M, (uint8_t)6);
	data->x = Wire.read();
	data->x += (Wire.read() << 8);
	data->y = Wire.read();
	data->y += (Wire.read() << 8);
	data->z = Wire.read();
	data->z += (Wire.read() << 8);

	data->x = data->x - data->x_offset;
	data->y = data->y - data->y_offset;
	data->z = data->z - data->z_offset;
	data->arg = atan2((float)-data->y, (float)data->x);

}

void set_gpsHiSpeed() {
	Serial_GPS.print("$PMTK220,100*2F\r\n");
	delay(100);
	Serial_GPS.print("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
	delay(100);
}
/*
long split_GPGGA(char msg[], char buff) {
	for (unsigned int i = 0; msg[i] != c; i++) {

	}
}*/

char get_gps_1() {
	while (1) {
		long data = Serial_GPS.read();
		if (data != -1) {
			char c = (char)data;
			return data;
		}
	}
}

long get_gps(struct gps *gps_data, unsigned long t) {
	gps_data->latitude = 0;
	gps_data->longitude = 0;
	gps_data->hh = 0;
	gps_data->mm = 0;
	gps_data->ss = 0;

	char c, gps_msg[100];
	long dd, mm, mmmm, ddd, dddd;
	unsigned long time = millis();

	while (Serial_GPS.available())Serial_GPS.read();

	while (millis()-time < t) {

		c = get_gps_1();
		if (c == '$') {
			for (long i = 0; i < 6; i++) {
				c = get_gps_1();
				gps_msg[i] = c;
			}
			if (strncmp(gps_msg, "GPGGA", 5) == 0) {
				for (long i = 0; c != '\n'; i++) {
					c = get_gps_1();
					gps_msg[i] = c;

					if (c == '\n') {
						gps_data->hh = 10 * (gps_msg[0] - 48) + (gps_msg[1] - 48);
						gps_data->mm = 10 * (gps_msg[2] - 48) + (gps_msg[3] - 48);
						gps_data->ss = 10 * (gps_msg[4] - 48) + (gps_msg[5] - 48);
						if (gps_msg[6] != '.')gps_data->mode = -1;
						gps_data->ms = 100 * (gps_msg[7] - 48) + 10*(gps_msg[8] - 48)+(gps_msg[9] - 48);
						if (gps_data->hh < 0 || gps_data->hh > 24)gps_data->mode = -1;

						
						if (i > 40) {
							long n;
							dd = 0;
							for (n = 5; n < i; n++) {
								if (gps_msg[n] == ',') {
									dd = 10 * (gps_msg[n + 1] - 48) + (gps_msg[n + 2] - 48);
									mm = 10 * (gps_msg[n + 3] - 48) + (gps_msg[n + 4] - 48);
									mmmm = 1000 * (gps_msg[n + 6] - 48) + 100 * (gps_msg[n + 7] - 48) + 10 * (gps_msg[n + 8] - 48) + (gps_msg[n + 9] - 48);

									gps_data->latitude = (dd + (((double)mm + (double)mmmm / 10000) / 60)) * 1000000;
									if (gps_msg[n + 10] != ',' || gps_msg[n + 11] != 'N')gps_data->mode = -1;
									break;
								}
							}
							for (n = n + 1; n < i; n++) {
								if (gps_msg[n] == 'N') {
									break;
								}
							}
							for (n = n + 1; n < i; n++) {
								if (gps_msg[n] == ',') {
									ddd = 100 * (gps_msg[n + 1] - 48) + 10 * (gps_msg[n + 2] - 48) + (gps_msg[n + 3] - 48);
									mm = 10 * (gps_msg[n + 4] - 48) + (gps_msg[n + 5] - 48);
									mmmm = 1000 * (gps_msg[n + 7] - 48) + 100 * (gps_msg[n + 8] - 48) + 10 * (gps_msg[n + 9] - 48) + (gps_msg[n + 10] - 48);
									gps_data->longitude = (ddd + (((double)mm + (double)mmmm / 10000) / 60)) * 1000000;
									if (gps_msg[n + 11] != ',' || gps_msg[n + 12] != 'E')gps_data->mode = -1;
									break;
								}
							}
							for (n = n + 1; n < i; n++) {
								if (gps_msg[n] == 'E') {
									break;
								}
							}
							for (n = n + 1; n < i; n++) {
								if (gps_msg[n] == ',') {
									gps_data->mode = (gps_msg[n + 1] - 48);
									break;
								}
							}
						}
						else {
							gps_data->mode = 0;
						}
						if (gps_data->mode == -1) {
							gps_data->latitude = 0;
							gps_data->longitude = 0;
						} else {
							return gps_data->mode;
						}
					}
				}
			}
		}
	}
	return -1;
}


void calc_gps(struct gps *gps_data, long latitude, long longitude) {
	
	long dx = latitude - gps_data->latitude;	//南北　北が正
	long dy = gps_data->longitude - longitude;	//東西　東が正
	gps_data->arg = atan2(dy, dx);
	gps_data->dist = dx * dx + dy * dy;
}

void print_data(control_data *data) {
	String str = "\n";

	str.concat("\nMODE         ");
	str.concat(data->mode);
	str.concat("           Log_num  ");
	str.concat(data->log_num);

	str.concat("\nTIME         ");
	str.concat(data->gps_data.hh);
	str.concat(":");
	str.concat(data->gps_data.mm);
	str.concat(":");
	str.concat(data->gps_data.ss);
	str.concat(".");
	str.concat(data->gps_data.ms);

	str.concat("\nPOWER        ");
	str.concat(data->voltage);
	str.concat("mV ");
	str.concat(data->current);
	str.concat("mA");

	str.concat("\nGPS          ");
	str.concat("mode:");
	str.concat(data->gps_data.mode);
	str.concat(" N: ");
	str.concat(data->gps_data.latitude);
	str.concat(" E: ");
	str.concat(data->gps_data.longitude);
	str.concat("  dist: ");
	str.concat(data->gps_data.dist);


	str.concat("\nLSM303       ");
	str.concat("x:");
	str.concat(data->LSM303_data.x);
	str.concat(" y:");
	str.concat(data->LSM303_data.y);


	str.concat("\nArg          ");
	str.concat(data->arg);
	str.concat(" (GPS: ");
	str.concat(data->gps_data.arg);
	str.concat(", LSM303: ");
	str.concat(data->LSM303_data.arg);
	str.concat(")");

	str.concat("\nFlight Pin   ");
	str.concat(data->flightPin);

	str.concat("\nmotor        (");
	str.concat(data->motor_L);
	str.concat(" , ");
	str.concat(data->motor_R);
	str.concat(")  nichrome: ");
	str.concat(data->nichrome);

	str.concat("\n");
	Serial_PC.print(str);
	return;
}

void write_data(control_data *data) {

	File logFile = SD.open(data->log_path, FILE_WRITE);

	String str = "";

	//A-B
	str.concat(data->log_num);
	str.concat(",");
	str.concat(data->mode);
	str.concat(",");

	//C-E
	str.concat(data->gps_data.hh);
	str.concat(",");
	str.concat(data->gps_data.mm);
	str.concat(",");
	str.concat(data->gps_data.ss);
	str.concat(".");
	str.concat(data->gps_data.ms);
	str.concat(",");

	//F-G
	str.concat(data->voltage);
	str.concat(",");
	str.concat(data->current);
	str.concat(",");

	//H-L
	str.concat(data->gps_data.latitude);
	str.concat(",");
	str.concat(data->gps_data.longitude);
	str.concat(",");
	str.concat(data->gps_data.mode);
	str.concat(",");
	str.concat(data->gps_data.arg);
	str.concat(",");
	str.concat(data->gps_data.dist);
	str.concat(",");

	//M-O
	str.concat(data->LSM303_data.x);
	str.concat(",");
	str.concat(data->LSM303_data.y);
	str.concat(",");
	str.concat(data->LSM303_data.arg);
	str.concat(",");

	//P
	str.concat(data->flightPin);
	str.concat(",");

	//Q
	str.concat(data->arg);
	str.concat(",");

	//R-T
	str.concat(data->motor_L);
	str.concat(",");
	str.concat(data->motor_R);
	str.concat(",");
	str.concat(data->nichrome);

	str.concat("\n");

	logFile.print(str);
	logFile.close();

	return;
}