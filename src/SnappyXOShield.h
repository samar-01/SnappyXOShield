#ifndef SNAPPYXOSHIELD_H
#define SNAPPYXOSHIELD_H

#include <Arduino.h>

// Motor Left Pins
const int motorLeft_InputOne = 4;
const int motorLeft_InputTwo = 7;
const int motorLeft_Enable = 5;

// Motor Right Pins
const int motorRight_InputOne = 8;
const int motorRight_InputTwo = 9;
const int motorRight_Enable = 6;

// Inversion flags — set via initMotors(invertL, invertR, invertLR)
static bool motorInvertL = false;
static bool motorInvertR = false;
static bool motorInvertLR = false;

void initMotors(bool invertL = false, bool invertR = false,
				bool invertLR = false) {
	motorInvertL = invertL;
	motorInvertR = invertR;
	motorInvertLR = invertLR;
	pinMode(motorLeft_InputOne, OUTPUT);
	pinMode(motorLeft_InputTwo, OUTPUT);
	pinMode(motorLeft_Enable, OUTPUT);
	pinMode(motorRight_InputOne, OUTPUT);
	pinMode(motorRight_InputTwo, OUTPUT);
	pinMode(motorRight_Enable, OUTPUT);
}

// Range: -255 to 255. Positive = forward, negative = backward.
void _motorWrite(int leftSpeed, int rightSpeed) {
	if (motorInvertLR) {
		int t = leftSpeed;
		leftSpeed = rightSpeed;
		rightSpeed = t;
	}
	if (motorInvertL) leftSpeed = -leftSpeed;
	if (motorInvertR) rightSpeed = -rightSpeed;

	bool leftFwd = leftSpeed >= 0;
	bool rightFwd = rightSpeed >= 0;

	digitalWrite(motorLeft_InputOne, leftFwd ? HIGH : LOW);
	digitalWrite(motorLeft_InputTwo, leftFwd ? LOW : HIGH);
	analogWrite(motorLeft_Enable, abs(leftSpeed));

	digitalWrite(motorRight_InputOne, rightFwd ? LOW : HIGH);
	digitalWrite(motorRight_InputTwo, rightFwd ? HIGH : LOW);
	analogWrite(motorRight_Enable, abs(rightSpeed));
}

void forward() { _motorWrite(255, 255); }
void forward(int speed) { _motorWrite(speed, speed); }
void reverse() { _motorWrite(-255, -255); }
void reverse(int speed) { _motorWrite(-speed, -speed); }
void turnLeft() { _motorWrite(-255, 255); }
void turnLeft(int speed) { _motorWrite(-speed, speed); }
void turnRight() { _motorWrite(255, -255); }
void turnRight(int speed) { _motorWrite(speed, -speed); }
void pause() { _motorWrite(0, 0); }
void brake() { _motorWrite(0, 0); }

// Joystick drive: throttle and steering each in range -512 to +512.
// Mixes them as a differential drive: left = throttle + steering, right =
// throttle - steering. Normalizes so the ratio is preserved when the sum
// exceeds the input range. Zero throttle + nonzero steering gives smooth
// in-place turns with no dead zone.
void drive(int throttle, int steering) {
	int left = throttle + steering;
	int right = throttle - steering;

	int maxVal = max(abs(left), abs(right));
	if (maxVal > 512) {
		left = left * 512 / maxVal;
		right = right * 512 / maxVal;
	}

	_motorWrite(left * 255 / 512, right * 255 / 512);
}

#endif
