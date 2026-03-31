#include "main.h"

void initialize() {
}

void disabled() {
	// chassis.set_coordinates(chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
	chassis.set_coordinates(cm_to_inch(-124.753),cm_to_inch(39.548), 0);
	// chassis.set_coordinates(0, 0, 0);
}


void competition_initialize() {
	init();
	claw.set_value(true);
}

void autonomous() {
	skills_init();
	skills_115();
}

void opcontrol() {
	while (true) {
		claw.set_value(false);
		chassis.control_arcade();
		delay(10);
	}
}