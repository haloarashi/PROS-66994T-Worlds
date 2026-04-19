#include "main.h"

IntakeTask intake_state = IntakeTask::STOP;

void square(float side_length){ // The effective side length of one tile is a little under 23.75 inches. The "little" is kinda negligible. 
    chassis.set_coordinates(0, 0, 0);
    chassis.drive_to_point(0, side_length);
    // chassis.DriveL.set_brake_mode_all(MotorBrake::brake);
    // chassis.DriveR.set_brake_mode_all(MotorBrake::brake);
    // chassis.DriveL.brake();
    // chassis.DriveR.brake();
    
    switch (chassis.DriveL.get_brake_mode(0)){
        case MotorBrake::coast:
        pros::screen::print(TEXT_LARGE_CENTER, 0, "coast");
        break;
        case MotorBrake::brake:
        pros::screen::print(TEXT_LARGE_CENTER, 0, "brake");
        break;
        case MotorBrake::hold:
        pros::screen::print(TEXT_LARGE_CENTER, 0, "hold");
        break;
        default:
        pros::screen::print(TEXT_LARGE_CENTER, 0, "error");
        break;
    }
    chassis.turn_to_angle(90);
    chassis.drive_to_point(side_length, side_length);
    chassis.turn_to_angle(180);
    chassis.drive_to_point(side_length, 0);
    chassis.turn_to_angle(270);
    chassis.drive_to_point(0, 0);
    chassis.turn_to_angle(0);
    chassis.drive_stop(MotorBrake::brake);
}
// Created during Skills 114 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

void red_parking_zone(){  // DONT USE THIS
    // intake_state = IntakeTask::INTAKE;
    // chassis.drive_with_voltage(50, 50);
    // delay(1000);
    // chassis.drive_with_voltage(-127, -127);
    // while(chassis.Gyro.get_yaw() > 175){
    //     delay(5);
    // }
    chassis.set_coordinates(24.35, 70.2, 270);
    exit_somewhere_skills(false, 300);
}

void sideways_parking_zone(bool left, bool red){
    int voltage = 60;
    bool facing_north = left == red;
    chassis.set_coordinates(0, 0, facing_north? 0 : 180);
    intake_state = IntakeTask::INTAKE;
    chassis.drive_with_voltage(voltage, voltage);
    // delay(500);
    wait_until([](){return progress >= 1;}, 5, 3000);
    delay(1100);
    shovel.set_value(true);
    wait_until([](){return progress >= 4;}, 5, 5000);
    // if(!red){
    //     delay(200);
    // }
    chassis.drive_stop(MotorBrake::brake);

    chassis.turn_to_angle(facing_north? 0 : 180); // change this if coming from the other side

    chassis.drive_with_voltage(-40, -40);
    delay(200); // delay to ensure robot has started driving backwards

    float heading = left == red? 0 : 180;
    
    chassis.wall_distance_condition([](){
        float avg_torque = (chassis.DriveL.get_torque(0) + chassis.DriveL.get_torque(1) + chassis.DriveL.get_torque(2) 
                          + chassis.DriveR.get_torque(0) + chassis.DriveR.get_torque(1) + chassis.DriveR.get_torque(2)) / 6.0;
        return avg_torque > 0.16;
    }, 3000, left? chassis.WallSide::LEFT : chassis.WallSide::RIGHT, -40, heading, left? 130 : 100);

    chassis.drive_stop(MotorBrake::hold);
    set_coordinates_start(red, facing_north);
}

float wheelbase = 13.25; // center dist between front and back wheels, in inches.
float distance_sensorL_offset = 3.25; // distance from left distance sensor to center of robot, in inches. This is a positive number.
float distance_sensorR_offset = 3.25; // distance from right distance sensor to center of robot, in inches. This is a positive number.

void set_coordinates_start(bool left, bool face_north){
    double left_dist = mm_to_inch(distance_sensorL.get()) + distance_sensorL_offset;
    double right_dist = mm_to_inch(distance_sensorR.get()) + distance_sensorR_offset;
    double dist = left? left_dist : right_dist;
    double dist_from_wall = fabs(dist * cos(to_rad(chassis.get_absolute_heading())));
    bool red = left == face_north;
    double new_x = red? dist_from_wall : 140.4 - dist_from_wall;
    chassis.set_coordinates(new_x, face_north? 70.2 + wheelbase/2 : 70.2 - wheelbase/2, chassis.get_absolute_heading());
    chassis.drive_stop(MotorBrake::brake);
    
    shovel.set_value(false);
    // exit
    // chassis.drive_with_voltage(left? 127 : 90, left? 90 : 127);
    // delay(150);
    intake_state = IntakeTask::INTAKE;
}

int progress = 0;
void sideways_parking_zone_tracking_task(bool add_extra_exit_condition){
    progress = 0;
    int timer = 0;

    wait_until_bool(chassis.Gyro.get_roll() < -6, 10, 0); // Acceleration on flat ground actually meets this condition D:
    progress = 1; // on bump

    wait_until_bool(chassis.Gyro.get_roll() > 1.5, 10, 0);
    progress = 2; // descending bump

    delay(2000);
    
    wait_until_bool(chassis.Gyro.get_roll() < -4.5, 1, 0);
    progress = 3; // on bump

    wait_until_bool(chassis.Gyro.get_roll() > 1.7, 1, 0);

    while(add_extra_exit_condition){
        if(0 > chassis.Gyro.get_roll() || chassis.Gyro.get_roll() > -4){
            timer += 10;
        }
        else{
            timer = 0;
        }
        if(timer >= 50){
            break;
        }
        delay(10);
    }

    progress = 4; // descending bump

}

void one_center_block_then_score(bool left, bool north){
    default_constants();
    intake_state = IntakeTask::INTAKE;
    // chassis.turn_to_point(left? 43.5 : 95, north? 92 : 50.4); // center block // 47, 93, 90, 50.4
    chassis.turn_to_angle(left? 95 : 256);
    // delay(100);
    // chassis.drive_max_voltage = 50;
    // chassis.drive_to_point(left? 43.5 : 95, left? 92 : 50.4); // center block // 47, 93, 90, 50.4
    chassis.drive_distance(50);
    // default_constants();
    
    bool upper = left == north;

    // turn to goal
    // chassis.turn_to_point(left? 56 : 83.4, north? 83 : 60.4, upper? 180 : 0);
    
    if(upper){
        chassis.turn_to_angle(north? 158 : 315, north? 179.0f : 180.0f);
        chassis.drive_with_voltage(-127, -127);
        delay(250);
        chassis.drive_with_voltage(-45, -45);
        delay(250);
        // chassis.turn_to_angle(north? 135 : 315, 180, -40.0f); // This is unnecessary because +-35 degrees work. 
        intake_state = IntakeTask::UPPER_GOAL_OUT;
        chassis.drive_with_voltage(127, 127);
        delay(50);
        // chassis.drive_with_voltage(-45, -45);
        // delay(700);
        // chassis.drive_distance(1);
    }
    else{
        shovel.set_value(false);
        chassis.turn_to_angle(north? 222 : 47); // 210
        // chassis.turn_to_point(80, 78);
        // chassis.turn_to_angle(225);
        // Task lower_task(sololower);
        chassis.drive_with_voltage(127, 127);
        delay(100);
        chassis.drive_with_voltage(45, 45);
        delay(180);
        // chassis.drive_with_voltage(127, 127);
        // delay(50);
        chassis.turn_timeout = 1000;
        chassis.motion_chain_turn_early_exit_range = 10;
        chassis.motion_chain_turn_min_voltage = 30;
        chassis.turn_to_angle(225, 0, 0, true); // extra 30.0f
        default_constants();
        intake_state = IntakeTask::LOWER_GOAL_OUT;
    }
    
    chassis.drive_stop(MotorBrake::brake);
    shovel.set_value(false);
    delay(upper? 3000 : 3000); // outtake 7 balls

    exit_somewhere_skills(upper, 150);
    if(upper){intake_state = IntakeTask::LONG_GOAL_OUT;}
}

void ball_clump(bool left){
    default_constants();
    Task intake_1([](){delay(100); intake_state = IntakeTask::INTAKE;});
    // chassis.turn_to_point(left? 45: 95.4, 40);
    chassis.turn_to_angle(left? 270 - 72 : 90 + 76);
    chassis.drive_error = 100; // random number to prevent early exit
    // Task shovel_task(ball_clump_shovel_task);
    // chassis.drive_settle_time = 90;
    // chassis.drive_to_point(left? 45: 95.4, 40);
    chassis.drive_distance(38, true); // clump
    chassis.drive_with_voltage(chassis.motion_chain_drive_min_voltage, chassis.motion_chain_drive_min_voltage);
    delay(200);
    // shovel_task.suspend();
    shovel.set_value(true);
}

// Created during Skills 82 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

int ball_clump_shovel_task(){
    wait_until([](){return chassis.drive_error < 5;}, 5, 1500);
    shovel.set_value(true);
    chassis.drive_max_voltage = 64;
    return 0;
}

void score_goal(int time, IntakeTask goal_type){
    chassis.drive_with_voltage(-103, -103);
    delay(300);
    intake_state = goal_type;
    delay(100);
    chassis.drive_stop(MotorBrake::coast);
    delay(time);
    intake_state = IntakeTask::STOP;
    exit_somewhere_skills(false, 150);
}

void loader(bool left, bool north, bool keep_intake_running){
    if(keep_intake_running){
        intake_state = IntakeTask::INTAKE;
    }
    // chassis.drive_to_point(x_prep, y);
    shovel.set_value(true);
    //   chassis.turn_kp = 3.29;
    //   chassis.turn_settle_error = 1.85;
    chassis.turn_to_angle(left? 271 : 90); // loader

    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    intake_state = IntakeTask::INTAKE;
    if((left && !north) || (!left && north)){
        chassis.wall_distance(chassis.WallSide::LEFT, 16.5, left? 270 : 90, 520, 50); // distance is relative
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, 16.5, left? 270 : 90, 527, 50);
    }
    intake_state = IntakeTask::INTAKE;
    chassis.drive_with_voltage(40, 40);
    delay(680);
    chassis.drive_with_voltage(14, 14);
    delay(1800);

//   int time = 0;
//   while(time < 1100){
//     chassis.drive_with_voltage(60, 10);
//     delay(300);
//     chassis.drive_with_voltage(10, 60);
//     delay(300);
//     time += 600;
//   }
}

void loader_from_goal(bool left, bool north){
    intake_state = IntakeTask::INTAKE;
    shovel.set_value(true);

    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    if((left && !north) || (!left && north)){
        chassis.wall_distance(chassis.WallSide::LEFT, 30, left? 270 : 90, 510, 50); // distance is relative
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, 30, left? 270 : 90, 527, 50);
    }
    chassis.drive_with_voltage(40, 40);
    delay(1500);
    chassis.drive_with_voltage(14, 14);
    delay(1000);
    // int time = 0;
    // while(time < 1100){
    //     chassis.drive_with_voltage(30, 0);
    //     delay(300);
    //     chassis.drive_with_voltage(0, 30);
    //     delay(300);
    //     time += 600;
    // }
}

void exit_somewhere_skills(bool drive_fwd, int time, bool reset_intake){
    if(reset_intake){
        intake_state = IntakeTask::INTAKE;
    }

    if(drive_fwd){
        chassis.drive_with_voltage(106, 106);
    }
    else{
        chassis.drive_with_voltage(-106, -106);
    }
    delay(time);
}

int wait_then_slow_down(){
    delay(300);
    for(int i = 0; i < 20; i++){
        chassis.drive_max_voltage -= 7; // yes 7 out of 127
        delay(10);
    }
    return 0;
}

void go_to_other_end_of_long_goal(bool target_is_left, bool north){
    // double x_target = target_is_left? 21 : 120.4;
    // double y_intermediate = north? 125 : 18;
    // double y_goal = north? 116.5 : 22;//113 : 30

    default_constants();
    chassis.turn_to_angle(north? 0 : 180);
    // chassis.drive_to_point(chassis.get_X_position(), y_intermediate);
    chassis.drive_settle_error = 3;
    chassis.drive_timeout = 1200;
    chassis.drive_distance(14.5);
    default_constants();
    chassis.turn_to_angle(target_is_left? 273 : 93);
    // chassis.pid_swing_set(RIGHT_SWING, target_is_left? 270 : 90, TURN_SPEED); // Northeast and southwest are right. The other two corners are left. ;
    // task slow_task;
    if((target_is_left && !north) || (!target_is_left && north)){
        // chassis.drive_with_voltage(90, 127);
        // wait(500, msec);
        // slow_task = task(wait_then_slow_down);
        chassis.wall_distance(chassis.WallSide::LEFT, 97, target_is_left? 270 : 90, 145, 40);
        // calibrate_coordinates(north? 4 : 2, true, false);
        chassis.turn_to_angle(north? 180 : 0);
        // calibrate_coordinates(north? 4 : 2, true, true);
    }
    else{
        // chassis.drive_with_voltage(127, 90);
        // wait(500, msec);
        // slow_task = task(wait_then_slow_down);
        chassis.wall_distance(chassis.WallSide::RIGHT, 101, target_is_left? 270 : 90, 100, 60);
        // calibrate_coordinates(north? 1 : 3, false, false);
        chassis.turn_to_angle(north? 180 : 0);
        // calibrate_coordinates(north? 1 : 3, false, true);
    }
    // slow_task.suspend();
    // default_constants();

    // wait(500, msec);
    // chassis.drive_with_voltage(127, 127);
    // wait(300, msec);
    // chassis.drive_with_voltage(64, 64);
    // wait(200, msec);

    // chassis.drive_with_voltage(18, 127);

    // chassis.turn_to_point(x_inter2, y_intermediate);
    // chassis.drive_to_point(x_inter2, y_intermediate);

    // chassis.turn_to_point(x_target, y_goal);
    // chassis.drive_to_point(x_target, y_goal);

    default_constants();
    // chassis.drive_to_point(chassis.get_X_position(), y_goal);
    chassis.drive_distance(target_is_left && north? 17 : 15);

    chassis.turn_to_angle(target_is_left? 270 : 90);
}

void score_long_goal(bool left, bool north, bool far){
    double x_goal = left? 40 : 100;
    double y = north? 116.97 : 22.5;

    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    if((left && !north) || (!left && north)){
        chassis.wall_distance(chassis.WallSide::LEFT, far? -21 : -30, left? 270 : 90, 495, 70);
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, far? -21 : -30, left? 270 : 90, 545, 70);
    }

    chassis.drive_with_voltage(-70, -70);
    delay(80);
    intake_state = IntakeTask::LONG_GOAL_OUT;
    delay(500);
    // chassis.drive_stop(MotorBrake::brake);
    chassis.drive_with_voltage(-45, -45);
    delay(1200);
    default_constants();
    // outtaketask.suspend();
}

// red is (left && north)
// blue is (!left && !north)
void drive_long_goal_to_parking_zone(bool red){
    default_constants();
    chassis.turn_to_angle(red? 240 : 60, false);
	chassis.drive_with_voltage(127, 127);
	delay(600);
    chassis.swing_to_angle(red? 190 : 10, false, true);

    default_constants();
    chassis.drive_with_voltage(70, 70);
	delay(500); // 200 gets the robot right in front of parking barrier
}

void park(){
    // chassis.pid_odom_set({{8, 30}, fwd, DRIVE_SPEED});
    // chassis.pid_wait(); //maybe quick chain
    // chassis.pid_turn_set({8, 70.2}, rev, TURN_SPEED);
    // chassis.pid_wait(); //maybe quick or quick chain
    // chassis.pid_odom_set({{8, 70.2}, rev, DRIVE_SPEED});

    chassis.drive_to_point(8, 30);
    chassis.turn_to_point(8, 70.2, 180);
    chassis.drive_to_point(8, 70.2);
}

void sideways_chain_park(){
    drive_long_goal_to_parking_zone(true);
    Task parking_zone_task([]{sideways_parking_zone_tracking_task(false);}); // maybe use true if necessary
    wait_until([](){return progress >= 3;}, 20, 1000);
    chassis.drive_with_voltage(25, 25);
    delay(500);
    chassis.drive_stop(MotorBrake::coast);
}

void fwd_park(){
    default_constants();
    chassis.turn_to_angle(180);
    // chassis.drive_to_point(chassis.get_X_position(), 67);
    chassis.drive_distance(53);
    chassis.turn_to_angle(270);
    chassis.drive_with_voltage(127, 127);
    while(true){
        delay(1000);
    }
}

/* @param corner
    1 = left north (0, 140.41)
    2 = right north (140.41, 140.41)
    3 = right south (140.41, 0)
    4 = left south (0, 0)

    I didn't write all corners! Add corners as needed. 
*/
void calibrate_coordinates(int corner, bool use_left_sensor, bool use_left_right_wall){
    // double heading = chassis.get_absolute_heading();
    // // bool face
    // if(315 < heading && heading <= 360 || heading < 45) 
    double left_dist = mm_to_inch(distance_sensorL.get()) + distance_sensorL_offset;
    double right_dist = mm_to_inch(distance_sensorR.get()) + distance_sensorR_offset;

    switch(corner){
        case 1:
            if(use_left_sensor){
                if(use_left_right_wall){
                    chassis.set_coordinates(left_dist, chassis.get_Y_position(), chassis.get_absolute_heading());
                }
                else{
                    chassis.set_coordinates(chassis.get_X_position(), 140.41 - left_dist, chassis.get_absolute_heading());
                }
            }
            // else{

            // }
            break;

        case 3:
            if(use_left_sensor){

            }
            else{
                if(use_left_right_wall){
                    chassis.set_coordinates(140.41 - right_dist, chassis.get_Y_position(), chassis.get_absolute_heading());
                }
                else{
                    chassis.set_coordinates(chassis.get_X_position(), right_dist, chassis.get_absolute_heading());
                }
            }
            break;
        
        default:
            break;
    }
}