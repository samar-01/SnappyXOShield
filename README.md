# SnappyXOShield

An Arduino library for simplified motor control with the [SnappyXO Motor Shield](https://github.com/samar-01/SnappyXOShield).

## Installation

1. Download the repository as a ZIP.
2. In the Arduino IDE: **Sketch → Include Library → Add .ZIP Library…** and select the downloaded file.
3. Alternatively, clone this repo into your Arduino `libraries/` folder.

## Pin Mapping

| Motor | IN1 | IN2 | Enable (PWM) |
|-------|-----|-----|--------------|
| Left  | 4   | 7   | 5            |
| Right | 8   | 9   | 6            |

## API

### `initMotors(invertL, invertR, invertLR)`

Call once in `setup()`. All parameters are optional and default to `false`.

| Parameter  | Description                                      |
|------------|--------------------------------------------------|
| `invertL`  | Reverse the left motor direction                 |
| `invertR`  | Reverse the right motor direction                |
| `invertLR` | Swap left and right motors entirely              |

### Movement Functions

| Function              | Description                                      |
|-----------------------|--------------------------------------------------|
| `forward()`           | Both motors full speed forward                   |
| `forward(speed)`      | Both motors forward at `speed` (0–255)           |
| `reverse()`           | Both motors full speed backward                  |
| `reverse(speed)`      | Both motors backward at `speed` (0–255)          |
| `turnLeft()`          | Spin left in place at full speed                 |
| `turnLeft(speed)`     | Spin left in place at `speed` (0–255)            |
| `turnRight()`         | Spin right in place at full speed                |
| `turnRight(speed)`    | Spin right in place at `speed` (0–255)           |
| `pause()` / `brake()` | Stop both motors                                 |

### `drive(throttle, steering)`

Joystick-style differential drive. Both inputs range from **-512 to +512**.

- `throttle`: forward/backward intensity
- `steering`: left/right intensity

The function mixes throttle and steering into left/right wheel speeds and normalizes the result so the speed ratio is preserved when the combined value would exceed the input range. Zero throttle with nonzero steering produces smooth in-place turns with no dead zone.

## Example

```cpp
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
```

See [`examples/BasicMotorControl/`](examples/BasicMotorControl/BasicMotorControl.ino) for the full sketch.

## Compatibility

- **SnappyXO Motor Shield:** v3.0.0+
