#include "main.h"

void skills_init(){
    if(intake_task == nullptr){
        intake_task = new Task(intake_status);
    }
    progress = 0;
    Task parking_zone_task([]{sideways_parking_zone_tracking_task(false);});
    
    // chassis.set_coordinates(29.804, 66.47, 180);
    default_constants();
    claw.set_value(true);
    lift.set_value(false);
}

void skills_115(){
    // chassis.set_coordinates(0, 0, 180);
    // set_coordinates_start(false, false);

    sideways_parking_zone(true, true);
    chassis.drive_with_voltage(127, 127);
    delay(200);
    one_center_block_then_score(true, true);

    ball_clump(true);
    default_constants();
    chassis.swing_to_angle(217, true, true);
    chassis.drive_distance(35);
    loader(true, false);
    exit_somewhere_skills(false, 150);
    shovel.set_value(false);

    //超強佬佬佬佬佬佬
    go_to_other_end_of_long_goal(false, false);
    score_long_goal(false, false, true);
    
    chassis.turn_to_angle(90);
    default_constants();
    loader_from_goal(false, false);
    score_long_goal(false, false, true);
    shovel.set_value(false);
    intake_state = IntakeTask::LONG_GOAL_OUT; // remove all blocks from robot for parking zone
   
	// vvvvvvvv blue parking zone vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    chassis.set_coordinates(0, 0, 90);
    default_constants();
    // chassis.turn_to_point(118, 35);
    chassis.turn_to_angle(60, false);
	chassis.drive_with_voltage(127, 127);
	delay(600);
    // chassis.swing_to_angle(90, true, false);
    chassis.swing_to_angle(10, false, true);
    // chassis.drive_settle_error = 6;
    // chassis.drive_to_point(118, 35);
    // chassis.turn_to_angle(0);

    // chassis.drive_settle_error = 4;
    // chassis.wall_kp = 0.35;
    // chassis.drive_kp = 6;
    // chassis.wall_distance(chassis.WallSide::RIGHT, 15, 0, 45, 80);
    default_constants();
    chassis.drive_with_voltage(70, 70);
	delay(500); // 200 gets the robot right in front of parking barrier
	// chassis.drive_with_voltage(-127, -127);
	// delay(10);
	// chassis.drive_stop(MotorBrake::hold);
	// delay(300);
    Task parking_zone_task([]{sideways_parking_zone_tracking_task(false);}); // maybe use true if necessary
    wait_until([](){return progress >= 1;}, 20, 1000);
    sideways_parking_zone(false, false);

    // // ^^^^^^^^ blue parking zone ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    // vvvvvvvvvv only needed if not doing lower goal vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // intake_state = IntakeTask::LONG_GOAL_OUT;

    // chassis.drive_to_point(110.596, 117);
    // chassis.turn_to_angle(90);
    // score_long_goal(false, true, false);
    
    // chassis.turn_settle_error = 1;
    // chassis.turn_timeout = 1000;
    // chassis.turn_to_angle(90);
    // default_constants();
    
    // loader_from_goal(false, true);

    // vvvvvvvvvv only needed if not doing lower goal ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    
    chassis.drive_with_voltage(127, 127);
    delay(200);
    one_center_block_then_score(false, true);

    default_constants();
    // chassis.turn_to_angle(220, true);
    // chassis.swing_to_angle(220, true, true);
    chassis.drive_distance(-28);
    intake_state = IntakeTask::INTAKE;
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
    
    fwd_park();
}

double measure_tracking_wheel_width(){
    // double spin_angle = 2.0;

    chassis.Fwd_tracker.set_position(0);
    chassis.set_heading(0);
    
    chassis.drive_with_voltage(30,-30);
    delay(100);

    while(chassis.get_absolute_heading()<350){
        // controller(primary).Screen.clearScreen();
        chassis.drive_with_voltage(30,-30);
        // controller(primary).Screen.print(chassis.get_absolute_heading());
        delay(10);
    }
    chassis.drive_stop(MotorBrake::hold);
    outtake.brake();

    double delta_straight = chassis.get_ForwardTracker_position();
    double delta_side = chassis.get_SidewaysTracker_position(); 

    // calculates tracker distances using arc length formula
    double FL = delta_straight / to_rad(chassis.get_absolute_heading());
    double SL = delta_side / to_rad(chassis.get_absolute_heading());

    pros::screen::erase();
    pros::screen::print(TEXT_MEDIUM, 0, "SL: %.2f", SL);
    pros::screen::print(TEXT_MEDIUM, 1, "FL: %.2f", FL);

    return 0.0;
}