// WARNING: This sketch is for the SnappyXO Motor Shield v2 ONLY.
// Do not upload this to a board using any other shield version.

#define SNAPPYXO_SHIELDV2
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
