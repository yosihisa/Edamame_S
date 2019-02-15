#include <Edamame_S.h>
#include <Edamame_S_EX.h>

void setup() {

}

void loop() {
  for (int speed = 0 ; speed < 255 ; speed++) {
    Motor(speed, speed);
    delay(20);
  }
  delay(1000);
  for (int speed = 255 ; speed >= 0 ; speed--) {
    Motor(speed, speed);
    delay(20);
  }
  delay(1000);

  Motor(0, 255);
  delay(1000);
  Motor(0, -255);
  delay(1000);

  Motor(255, 0);
  delay(1000);
  Motor(-255, 0);
  delay(1000);


}
