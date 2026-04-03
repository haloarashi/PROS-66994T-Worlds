#include "main.h"

void initialize() {
}

void disabled() {
}


void competition_initialize() {
	init();
	claw.set_value(true);
}

ASSET(curveLeft_txt);

void autonomous() {
	chassis.set_coordinates(0, 0, 0);
    inertial.tare_euler(); // idk the difference between this and inertial.tare(). Both works. Does not work if called in competition_initialize() for some reason. 
	skills_init();
	skills_115();
	// chassis.drive_stop(MotorBrake::brake);
}

void opcontrol() {
	inertial.tare_euler(); // idk the difference between this and inertial.tare(). Both works. Does not work if called in competition_initialize() for some reason. 
	while (true) {
		claw.set_value(false);
		chassis.control_arcade();
		delay(10);
	}
}