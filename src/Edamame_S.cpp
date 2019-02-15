#include "Edamame_S.h"


void LSM303_init_m(){
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

void LSM303_update_m(struct xyza *data){

    Wire.beginTransmission(LSM303AGR_M);
    Wire.write(0x60);
    Wire.write(0b00001101);  
    Wire.endTransmission(true);

    Wire.beginTransmission(LSM303AGR_M);
    Wire.write(0x68);
    Wire.endTransmission(false);
    Wire.requestFrom((uint8_t)LSM303AGR_M, (uint8_t)6);
    data->x = Wire.read();
    data->x += (Wire.read()<<8);
    data->y = Wire.read();
    data->y += (Wire.read()<<8);
    data->z = Wire.read();
    data->z += (Wire.read()<<8);

    data->x = data->x - data->x_offset;
    data->y = data->y - data->y_offset;
    data->z = data->z - data->z_offset;
    data->arg = -1.0 * atan2((float) -data->y, (float)data->x);

}