#include "Edamame_S.h"

void setup() {
  pinMode( LED0, OUTPUT );
  pinMode( LED1, OUTPUT );
}

void loop() {
  digitalWrite( LED0, HIGH );
  digitalWrite( LED1, HIGH );
  delay( 500 );
  digitalWrite( LED0, LOW );
  digitalWrite( LED1, LOW );
  delay( 500 );
}
