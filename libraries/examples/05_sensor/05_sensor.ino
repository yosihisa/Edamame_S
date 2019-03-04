#include <Edamame_S.h>
#include <Edamame_S_EX.h>

struct xyza LSM303_data;

void setup() {

  Wire.begin();

  Serial_PC.begin(115200);
  Serial_PC.print("Hello sensor test\n");

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
  
  Serial_PC.print(ina226_voltage());
  Serial_PC.print("[mV] ");
  Serial_PC.print(ina226_current());
  Serial_PC.println("[mA]");
  Motor(230, 230);
  delay(500);
}
