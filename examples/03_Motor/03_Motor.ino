#include <Edamame_S.h>
#include <Edamame_S_EX.h>

void setup() {

}

void loop() {
  for (int speed = 0 ; speed < 255 ; speed++) {
    motor(speed, speed);
    delay(20);
  }
  delay(1000);
  for (int speed = 255 ; speed >= 0 ; speed--) {
    motor(speed, speed);
    delay(20);
  }
  delay(1000);

  motor(0, 255);
  delay(1000);
  Motor(0, -255);
  delay(1000);

  motor(255, 0);
  delay(1000);
  motor(-255, 0);
  delay(1000);


}
