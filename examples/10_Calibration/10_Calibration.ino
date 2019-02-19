#include <Edamame_S.h>
#include <Edamame_S_EX.h>

struct control_data cansat;


void setup() {

	Wire.begin();

	Serial_PC.begin(115200);
	Serial_GPS.begin(9600);
	Serial_PC.print("Hello Calibration test\n");

	ina226_init();
	LSM303_init_m();
	set_gpsHiSpeed();

}

void loop() {
	//unsigned long t = millis();
	update(&cansat);

	//apply(&cansat);
	print_data(&cansat);
	//write_data(&cansat);

	cansat.log_num++;
	cansat.mode = 1;
	//delay(500);
	//while (millis() - t < 500);
}

void update(control_data *data) {
	LSM303_update_m(&data->LSM303_data);
	data->voltage = ina226_voltage();
	data->current = ina226_current();
	get_gps(&data->gps_data, 500);
	
	//calc_gps
}

void apply(control_data *data) {

}