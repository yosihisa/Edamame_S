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
	data->arg = -1.0 * atan2((float)-data->y, (float)data->x);

}

void set_gpsHiSpeed() {
	Serial_GPS.print("$PMTK220,100*2F\r\n");
	Serial_GPS.print("$PMTK314,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0*29\r\n");
}

long get_gps(struct gps *gps_data, long t) {
	gps_data->latitude = 0;
	gps_data->longitude = 0;
	gps_data->hh = 0;
	gps_data->mm = 0;
	gps_data->ss = 0;
	gps_data->ms = 0;

	long timeout = millis();

	long dddmm, mmmm;
	long ddd, dddd;
	long hhmmss, sss;
	char gps_msg[100];
	long i = 0;

	while (1) {
		//TIME OUT
		if (t < millis() - timeout) {
			return -1;
		}
		long c = Serial_GPS.read();
		if (c != -1) {
			gps_msg[i] = (char)c;
			i++;
		} else {
			continue;
		}

		if (gps_msg[i - 1] == '\n') {

			if (strncmp(gps_msg, "$GPGGA", 6) == 0) {

				strtok(gps_msg, ","); //$GPGGA,

				hhmmss	= atol(strtok(NULL, "."));
				sss		= atol(strtok(NULL, ","));
				gps_data->hh = (hhmmss/10000);
				gps_data->mm = (hhmmss%10000)/100;
				gps_data->ss = (hhmmss%100);
				gps_data->ms = sss;

				//latitude
				dddmm = atol(strtok(NULL, "."));
				mmmm  = atol(strtok(NULL, ","));
				ddd = dddmm / 100;
				dddd = (((dddmm%100)*10000 + mmmm))*10 / 6;
				gps_data->latitude = ddd * 1000000 + dddd;

				strtok(NULL, ","); //N or S

				//longitude
				dddmm = atol(strtok(NULL, "."));
				mmmm = atol(strtok(NULL, ","));
				ddd = dddmm / 100;
				dddd = (((dddmm % 100) * 10000 + mmmm))*10 / 6;
				gps_data->longitude = ddd * 1000000 + dddd;

				strtok(NULL, ","); //E or S
				
				return atol(strtok(NULL, ","));

			} else {

				i = 0;

			}
		}
	}
}

