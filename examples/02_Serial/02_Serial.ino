#include <Edamame_S.h>

void setup() {
  Serial_PC.begin(115200);
  Serial_PC.print("Hello SOMESAT\n");
}

void loop() {
  Serial_PC.print("Hello SOMESAT\n");
  delay(1000);
}
