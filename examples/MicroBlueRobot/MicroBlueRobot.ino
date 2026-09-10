// This example shows driving with the MicroBlue app with Arduino R4 Wifi. Must install MicroBlue library to use.

#include <MicroBlue.h>
#include <SnappyXOShield.h>
MicroBlueManager manager;

void setup() {
	initMotors();
	manager.begin("My BLE Module");
}

void loop() {
	MicroBlueMessage msg = manager.read();

	if (msg.id == "d0" || msg.id == "d1") {
		int throttle, steering;
		sscanf(msg.value.c_str(), "%d,%d", &steering, &throttle);
		throttle -= 512;
		steering -= 512;
		drive(throttle, steering);
	}
}
