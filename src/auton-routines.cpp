#include "main.h"

void skills_init(){
    Task in_fxn(intake_status);
    progress = 0;
    Task parking_zone_task(sideways_parking_zone_tracking_task, (void*)false);
    
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
    // chassis.drive_distance(32.5);
    // chassis.turn_to_point(29.804, 24);
    // chassis.turn_to_point(chassis.get_X_position(), 24);
    // shovel.set_value(false);

    loader(true, false);
    exit_somewhere_skills(false, 150);
    shovel.set_value(false);

    double left_dist = mm_to_inch(distance_sensorL.get()) + 3.25;
    double dist_from_wall = fabs(left_dist * sin(to_rad(chassis.get_absolute_heading())));
    chassis.set_coordinates(chassis.get_X_position(), dist_from_wall, chassis.get_absolute_heading());
    // pros::screen::print(TEXT_MEDIUM, 1, "Y adjusted to %.2f", dist_from_wall);
    // pros::screen::print(TEXT_MEDIUM, 2, "distance %.2f", left_dist);
    
    go_to_other_end_of_long_goal(false, false);
    score_long_goal(false, false, false);
    
    // chassis.turn_settle_error = 1;
    // chassis.turn_timeout = 1000;
    chassis.turn_to_angle(90);
    default_constants();
    
    loader_from_goal(false, false);
    shovel.set_value(false);
    //超強佬佬佬佬佬佬
    score_long_goal(false, false, false);
    delay(1000); // this is too long if we're also doing lower goal
    exit_somewhere_skills(true, 150, false);
    intake_task = IntakeTask::LONG_GOAL_OUT;
    // intake_task = IntakeTask::LONG_GOAL_OUT; // remove all blocks from robot for parking zone

    // // ^^^^ first half done ^^^^

    // chassis.turn_to_point(118, 35);
    // chassis.drive_settle_error = 6;
    // chassis.drive_to_point(118, 35);
    // chassis.turn_to_angle(0);

    // odomlift.set_value(true);
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "AAAA before right_wall");
    // chassis.drive_settle_error = 4;
    // chassis.wall_kp = 0.35;
    // chassis.drive_kp = 6;
    // chassis.min_right_wall_distance(15, 0, 45, 80);
    // default_constants();
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "BBBB before voltage");
    // chassis.drive_with_voltage(80, 70);
    // Task parking_zone_task(sideways_parking_zone_tracking_task, (void*)true); // change this to true for actual skills!
    // wait_until([](){return progress >= 1;}, 20, 1000);
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "CCCC before parking zone");
    // sideways_parking_zone(false, false);

    // // ^^^^^^^^ blue parking zone ^^^^^^^^^^^

    // one_center_block_then_score(false, true);
    // intake_task = IntakeTask::LONG_GOAL_OUT;
    
    // chassis.set_coordinates(chassis.get_X_position(), chassis.get_Y_position() + 7, chassis.get_absolute_heading());
    chassis.turn_to_point(110.596, 117);
    default_constants();
    shovel.set_value(false);

    // only needed if not doing lower goal vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // intake_task = IntakeTask::LONG_GOAL_OUT;

    // chassis.drive_to_point(110.596, 117);
    // chassis.turn_to_angle(90);
    // score_long_goal(false, true, false);
    
    // chassis.turn_settle_error = 1;
    // chassis.turn_timeout = 1000;
    // chassis.turn_to_angle(90);
    // default_constants();
    
    // loader_from_goal(false, true);

    // only needed if not doing lower goal ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    loader(false, true, false);
    exit_somewhere_skills(false, 150);
    shovel.set_value(false);
    
    go_to_other_end_of_long_goal(true, true);
    score_long_goal(true, true, false);
    
    chassis.turn_settle_error = 1;
    chassis.turn_timeout = 1000;
    chassis.turn_to_angle(270);
    default_constants();
    
    loader_from_goal(true, true);
    shovel.set_value(false);
    
    score_long_goal(true, true, true);
    delay(1000); // this is too long if we're also doing lower goal
    exit_somewhere_skills(true, 200, false);
    intake_task = IntakeTask::LONG_GOAL_OUT;
    
    // // park
    default_constants();
    chassis.turn_to_angle(180);
    intake_task = IntakeTask::LONG_GOAL_OUT;
    chassis.drive_to_point(chassis.get_X_position(), 67);
    intake_task = IntakeTask::LONG_GOAL_OUT;
    chassis.turn_to_angle(270);
    intake_task = IntakeTask::LONG_GOAL_OUT;
    chassis.drive_with_voltage(127, 127);
    intake_task = IntakeTask::LONG_GOAL_OUT;

    // // ------------------------------------------------------------------
    // chassis.turn_to_point(12, 106);
    // chassis.drive_settle_error = 6;
    // chassis.drive_to_point(12, 106);
    // chassis.turn_to_angle(270);
    // chassis.drive_with_voltage(60, 60);
    // delay(1000);
    // chassis.turn_to_angle(180);

    // odomlift.set_value(true);
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "AAAA before right_wall");
    // // chassis.drive_settle_error = 4;
    // // chassis.wall_kp = 0.35;
    // // chassis.drive_kp = 6;
    // // chassis.min_right_wall_distance(15, 0, 45, 80);
    // // default_constants();
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "BBBB before voltage");
    // chassis.drive_with_voltage(80, 70);
    // Task parking_zone_task(sideways_parking_zone_tracking_task, (void*)true); // change this to true for actual skills!
    // wait_until([](){return progress >= 1;}, 20, 1000);
    // // pros::screen::print(TEXT_LARGE_CENTER, 1, "CCCC before parking zone");
    // // sideways_parking_zone(false, false);

    // int voltage = 85;
    // chassis.set_coordinates(0, 0, chassis.get_absolute_heading());
    // odomlift.set_value(true);
    // intake_task = 1;
    // chassis.drive_with_voltage(voltage, voltage);
    // // delay(500);
    // wait_until([](){return progress >= 3;}, 5, 3000);
    // delay(1000);
    // chassis.drive_with_voltage(-35, -35);
    // delay(1000);
    // chassis.drive_stop(MotorBrake::brake);

    // // ------------------------------------------------------------------

    // // chassis.drive_stop(MotorBrake::brake);
}

double measure_tracking_wheel_width()
{
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