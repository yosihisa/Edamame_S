#include "Edamame_S_EX.h"

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

void Motor(int L ,int R){
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

void Nichrome(int power){
    analogWrite(NICHROME,power);
}