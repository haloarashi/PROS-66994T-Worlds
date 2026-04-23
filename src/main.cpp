#include "main.h"

Task* intake_task = nullptr;

void initialize() {
}

void disabled() {
	intake_state = IntakeTask::STOP;
	delay(1000);
	inertial.tare_euler(); // idk the difference between this and inertial.tare(). Both works. Does not work if called in competition_initialize() or disabled() for some reason. 
}


void competition_initialize() {
	init();
	claw.set_value(true);
	shovel.set_value(false);
	delay(2200);
	inertial.tare_euler(); // idk the difference between this and inertial.tare(). Both works. Does not work if called in competition_initialize() or disabled() for some reason.
}

ASSET(curveLeft_txt);

void autonomous() {
	chassis.set_coordinates(0, 0, 0);
	skills_init();
	skills_115();
}

bool last_bt_x = false;
bool bt_x = false;

void opcontrol() {
	if(intake_task == nullptr){
		intake_task = new Task(intake_status);
    }
	
	Controller master(CONTROLLER_MASTER);
	intake_state = IntakeTask::STOP;
	shovel.set_value(false);
	chassis.drive_stop(MotorBrake::brake);
	// delay(1000); // make sure robot is at rest so that inertial.tare_euler() resets values properly
	// inertial.tare_euler(); // idk the difference between this and inertial.tare(). Both works. Does not work if called in competition_initialize() or disabled() for some reason. 
	while (true) {
		chassis.control_arcade();
	}
}