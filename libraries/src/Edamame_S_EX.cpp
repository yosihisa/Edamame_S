#include "Edamame_S_EX.h"
#include "Edamame_S.h"

const byte INA226_CONFIG = 0x00;
const byte INA226_SHUNTV = 0x01;
const byte INA226_BUSV   = 0x02;
const byte INA226_POWER  = 0x03;
const byte INA226_CURRENT = 0x04;
const byte INA226_CALIB  = 0x05;
const byte INA226_MASK   = 0x06;
const byte INA226_ALERTL = 0x07;
const byte INA226_DIE_ID = 0xff;

void INA226_write(byte reg, unsigned short val){
    Wire.beginTransmission(INA226_ADDR);
    Wire.write(reg);
    Wire.write(val >> 8);
    Wire.write(val & 0xff);
    Wire.endTransmission();  
}

short INA226_read(byte reg){
    short ret = 0;
    Wire.beginTransmission(INA226_ADDR);
    Wire.write(reg);
    Wire.endTransmission();  
    Wire.requestFrom((int)INA226_ADDR, 2);
    while(Wire.available()) {
        ret = (ret << 8) | Wire.read();
    }
    return ret;
}

void ina226_init(){
    INA226_write(INA226_CONFIG, 0x45ff);
	INA226_write(INA226_CALIB, 512);
}

long ina226_voltage(){
	return 1.25*INA226_read(INA226_BUSV);
}

long ina226_current(){
    return INA226_read(INA226_CURRENT);
}

void set_pinMode() {
	pinMode(LED0, OUTPUT);
	pinMode(LED1, OUTPUT);

	pinMode(NICHROME, OUTPUT);
	pinMode(MOTOR_LF, OUTPUT);
	pinMode(MOTOR_LR, OUTPUT);
	pinMode(MOTOR_RF, OUTPUT);
	pinMode(MOTOR_RR, OUTPUT);
	pinMode(FLIGHT_PIN, INPUT);

	analogWrite(NICHROME, 0);

}
void motor(int L ,int R){
    if(L>=0){
        analogWrite(MOTOR_LF, L);
        analogWrite(MOTOR_LR, 0);
    }else{
        analogWrite(MOTOR_LF, 0);
        analogWrite(MOTOR_LR, -L);
    }

    if(R>=0){
        analogWrite(MOTOR_RF, R);
        analogWrite(MOTOR_RR, 0);
    }else{
        analogWrite(MOTOR_RF, 0);
        analogWrite(MOTOR_RR, -R);
    }
}

void nichrome(int power){
    analogWrite(NICHROME,power);
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