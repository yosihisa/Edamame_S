#include <Edamame_S.h>

struct gps gps_data;

void setup() {

	Serial_PC.begin(115200);
	Serial_GPS.begin(9600);
	Serial_PC.println("Hello GPS test");
	delay(100);
	set_gpsHiSpeed();
	
}
void loop() {
	get_gps(&gps_data,500);


	String str = "";
	
	str.concat(gps_data.mode);
	str.concat(" ");
	str.concat(gps_data.hh);
	str.concat(":");
	str.concat(gps_data.mm);
	str.concat(":");
	str.concat(gps_data.ss);
	str.concat(".");
	str.concat(gps_data.ms);
	str.concat(" ");

	str.concat(gps_data.latitude);
	str.concat(",");
	str.concat(gps_data.longitude);
	str.concat("\n");
	
	Serial_PC.print(str);
}
