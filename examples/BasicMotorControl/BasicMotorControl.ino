#include <SnappyXOShield.h>

void setup() {
  initMotors();
}

void loop() {
  forward();
  delay(1000);

  reverse();
  delay(1000);

  turnLeft();
  delay(500);

  turnRight();
  delay(500);

  pause();
  delay(1000);
}
