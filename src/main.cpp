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
	// skills_115();
	chassis.drive_with_voltage(80, 80);
    delay(200);
    one_center_block_then_score(false, true);

    default_constants();
    intake_state = IntakeTask::LONG_GOAL_OUT;
    chassis.drive_distance(-28, true);
    chassis.swing_to_angle(180, true, true);
    chassis.drive_distance(-17);
    loader(false, true);
    exit_somewhere_skills(false, 150);
    shovel.set_value(false);

    //超強佬佬佬佬佬佬
    go_to_other_end_of_long_goal(true, true);
    score_long_goal(true, true, true);
    
    chassis.turn_to_angle(270);
    default_constants();
    loader_from_goal(true, true);
    score_long_goal(true, true, true);
    shovel.set_value(false);   
    exit_somewhere_skills(true, 200, false);
    intake_state = IntakeTask::LONG_GOAL_OUT; // remove all blocks from robot for parking zone
    
    // fwd_park();
    sideways_chain_park();
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