#include <Edamame_S.h>
#include <Edamame_S_EX.h>

struct xyza LSM303_data;

void setup() {

  Wire.begin();

  Serial_PC.begin(9600);
  Serial_PC.print("Hello SOMESAT\n");

  ina226_init();
  LSM303_init_m();
}

void loop() {
  LSM303_update_m(&LSM303_data);
  Serial_PC.print("X:");
  Serial_PC.print(LSM303_data.x);
  Serial_PC.print("  Y:");
  Serial_PC.print(LSM303_data.y);
  Serial_PC.print("  Z:");
  Serial_PC.print(LSM303_data.z);
  
  Serial_PC.print("   ");
  
  Serial_PC.print(ina226_voltage(), 3);
  Serial_PC.print("[V]");
  Serial_PC.print(ina226_current(), 3);
  Serial_PC.println("[A]");
  delay(500);
}
