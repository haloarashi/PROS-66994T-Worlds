#include "main.h"

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(127, 4.7625, 0, 21.167, 0, 0); // max 127
  chassis.set_heading_constants(64, 7, 0, 20, 0); 
  chassis.set_turn_constants(105.833333, 2.54, .105833333, 17.4625, 15.0); // max 105
  chassis.set_swing_constants(116.4166667, 3.704166667, 0.08466667, 21.1666667, 15);
  chassis.set_wall_constants(127, 0.449791666666667, 0, 0, 0);
  //chassis.set_drive_min_constants(12, 1.45, 0, 2, 0, 1.5);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.8, 50, 3000);
  chassis.set_turn_exit_conditions(1.82, 50, 2000);
  chassis.set_swing_exit_conditions(1, 250, 3000);
}

int intake_task;

// void default_constants(){
//   // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
//   chassis.set_drive_constants(127, 2.58, 0, 0, 0, 0); // max 127
//   chassis.set_heading_constants(64, 7, 0, 20, 0); 
//   chassis.set_turn_constants(105, 3, .05, 20.0, 15.0); // max 105
//   chassis.set_swing_constants(113, 6, 0, 65, 0);
//   chassis.set_wall_constants(82, 1.30, 0, 0, 0);
//   //chassis.set_drive_min_constants(12, 1.45, 0, 2, 0, 1.5);

//   // Each exit condition set is in the form of (settle_error, settle_time, timeout).
//   chassis.set_drive_exit_conditions(1.8, 115, 3000);
//   chassis.set_turn_exit_conditions(1.82, 75, 2000);
//   chassis.set_swing_exit_conditions(1, 250, 3000);
// }

void square(){
    chassis.set_coordinates(0, 0, 0);
    chassis.drive_to_point(0, 48);
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
    chassis.drive_to_point(48, 48);
    chassis.turn_to_angle(180);
    chassis.drive_to_point(48, 0);
    chassis.turn_to_angle(270);
    chassis.drive_to_point(0, 0);
    chassis.turn_to_angle(0);
    chassis.drive_stop(MotorBrake::brake);
}
// Created during Skills 114 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

void red_parking_zone(){  // DONT USE THIS
    // intake_task = 1;
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
    int voltage = 85;
    chassis.set_coordinates(0, 0, left? 0 : chassis.get_absolute_heading());
    intake_task = 1;
    chassis.drive_with_voltage(voltage, voltage);
    // delay(500);
    wait_until([](){return progress >= 1;}, 5, 3000);
    delay(red? 900 : 900);
    shovel.set_value(true);
    wait_until([](){return progress >= 4;}, 5, 5000);
    // if(!red){
    //     delay(200);
    // }
    chassis.drive_stop(MotorBrake::brake);

    chassis.turn_to_angle(0); // change this if coming from the other side

    chassis.drive_with_voltage(-37, -37);
    chassis.set_coordinates(0, 0, chassis.get_absolute_heading());
    delay(500); // delay to ensure robot has started driving backwards

    double prev_pos = chassis.get_Y_position() - 10; // -10 is a random offset to ensure the loop starts
    while(true){
        delay(200);
        double current_pos = chassis.get_Y_position();
        double threshold = 0.15;
        if(fabs(current_pos - prev_pos) < threshold){
            break;
        }
        prev_pos = current_pos;
    }

    chassis.drive_stop(MotorBrake::hold);
    set_coordinates_start(left, red);
}

void set_coordinates_start(bool left, bool face_north){
    double left_dist = mm_to_inch(distance_sensorL.get()) + 5.75;
    double right_dist = mm_to_inch(distance_sensorR.get()) + 5.25;
    double dist = left? left_dist : right_dist;
    double dist_from_wall = fabs(dist * cos(to_rad(chassis.get_absolute_heading())));
    double new_x;
    // double new_x = left? dist_from_wall : 140.4 - dist_from_wall;
    // if(left && face_north || !left && !face_north){
    //     new_x = 140.4 - dist_from_wall;
    // }
    // else{
        new_x = dist_from_wall;
    // }
    chassis.set_coordinates(new_x, face_north? 85.35 : 55.05, chassis.get_absolute_heading());
    chassis.drive_stop(MotorBrake::brake);
    
    shovel.set_value(false);
    // exit
    // chassis.drive_with_voltage(left? 127 : 90, left? 90 : 127);
    // delay(150);
    intake_task = 1;
}

int progress = 0;
void sideways_parking_zone_tracking_task(void* far){ // TODO: finish this function
    bool far_bool = (bool)far;
    progress = 0;
    int timer = 0;

    wait_until_bool(chassis.Gyro.get_pitch() > 6, 10, 0);
    progress = 1; // on bump

    wait_until_bool(chassis.Gyro.get_pitch() < -1.5, 10, 0);
    progress = 2; // descending bump

    delay(2000);
    
    wait_until_bool(chassis.Gyro.get_pitch() > 4.5, 10, 0);
    progress = 3; // on bump

    wait_until_bool(chassis.Gyro.get_pitch() < -1.5, 10, 0);

    while(far_bool){
        if(0 < chassis.Gyro.get_pitch() && chassis.Gyro.get_pitch() < 4){
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
    // chassis.turn_kp = 3.29;
    // chassis.turn_to_point(left? 56 : 86, north? 81 : 50);
    // // chassis.drive_kp = 24.58;
    // // chassis.drive_settle_time = 90;
    // chassis.drive_to_point(left? 56 : 86, north? 81 : 55);
    intake_task = 1;
    chassis.turn_to_point(left? 43.5 : 95, north? 92 : 50.4); // center block // 47, 93, 90, 50.4
    // delay(100);
    // chassis.drive_max_voltage = 50;
    chassis.drive_to_point(left? 43.5 : 95, left? 93 : 90); // center block // 47, 93, 90, 50.4

    default_constants();
    
    bool upper = (left && north) || (!left && !north);

    if(upper){
        // chassis.turn_to_point(left? 58 : 76, north? 81 : 60, 180); // goal
        chassis.turn_to_point(left? 56 : 83.4, north? 83 : 60.4, 180); // goal
        // Task upper_task(soloupper);
        // chassis.drive_to_point(left? 61 : 76, north? 83 : 60);
        chassis.drive_with_voltage(-127, -127);
        delay(100);
        chassis.drive_with_voltage(-45, -45);
        delay(700);
        chassis.drive_distance(1);
        intake_task = 4;
    }
    else{
        // chassis.turn_kp = 3.25;
        // chassis.turn_to_angle(45);
        chassis.turn_to_point(80, 78);
        shovel.set_value(false);
        // chassis.drive_to_point(79, 79);
        // chassis.turn_to_angle(225);
        // Task lower_task(sololower);
        chassis.drive_with_voltage(90, 90);
        delay(400);
        chassis.drive_with_voltage(35, 35);
        delay(100);
        intake_task = 10;
    }
    
    chassis.drive_stop(MotorBrake::brake);
    shovel.set_value(false);
    intake_task = upper? 4 : 10;
    if(upper){
        delay(1000); // outtake 7 balls // upper 2000 total if we're also doing lower
        intake_task = 4;
        delay(2000);
    }
    else{
        delay(1500); // outtake 7 balls
    }
    // delay(upper? 3000 : 1500); // outtake 7 balls 
    intake_task = upper? 4 : 8;
    
    // intake_task = 1; // dont go back to 1 here bc if excess blue blocks arent cleared out, the next section is doomed
    if(upper){
        chassis.drive_with_voltage(40, 40);
        delay(100);
        exit_somewhere_skills(true, 150);
        intake_task = 2;
    }
    else{
        intake_task = 2;
        chassis.drive_with_voltage(-30, -30);
        delay(100);
        exit_somewhere_skills(false, 150);
        chassis.drive_stop(MotorBrake::brake);
        delay(100);
    }
}

void ball_clump(bool left){
    default_constants();
    Task intake_1([](){delay(100); intake_task = 1;});
    chassis.turn_to_point(left? 45: 95.4, 40);
    chassis.drive_error = 100; // random number to prevent early exit
    Task drive_task(get_ball_clump_task_2);
    // chassis.drive_kp = 24.58;
    chassis.drive_settle_time = 90;
    chassis.drive_to_point(left? 45: 95.4, 40);
    // drive_task.suspend(); //
    shovel.set_value(true);
    chassis.drive_stop(MotorBrake::brake);
}

// void one_center_block_then_score(bool left, bool north){
//     default_constants();
//     // chassis.turn_kp = 3.29;
//     chassis.turn_to_point(left? 58.65 : 86, north? 80 : 50);
//     // chassis.drive_kp = 24.58;
//     // chassis.drive_settle_time = 90;
//     chassis.drive_to_point(left? 52 : 86, north? 78 : 55);
//     chassis.turn_to_point(left? 48.5 : 92, north? 87: 48); // center block
//     delay(100);
//     chassis.drive_max_voltage = 50;
//     chassis.drive_to_point(left? 48.5 : 90, north? 87 : 50); // center block

//     default_constants();
    
//     bool upper = (left && north) || (!left && !north);

//     if(upper){
//         Task upper_task(soloupper);
//         chassis.turn_to_point(left? 52 : 76, north? 83 : 60, 180); // goal
//         // chassis.drive_to_point(left? 61 : 76, north? 83 : 60);
//         chassis.drive_with_voltage(-75, -75);
//         delay(300);
//     }
//     else{
//         chassis.turn_kp = 3.25;
//         // chassis.turn_to_angle(45);
//         chassis.turn_to_point(left? 61 : 76, north? 83 : 60);
//         shovel.set_value(false);
//         Task lower_task(sololower);
//         chassis.drive_with_voltage(75, 75);
//         delay(1000);
//     }
    
//     chassis.drive_stop(MotorBrake::brake);
//     shovel.set_value(false);
//     delay(1000); // outtake 7 balls

//     exit_somewhere_skills(true, 150);
// }

// int soloupper(){
//   delay(750);
//   intake_task = 4;
//   return 0;
// }

// Created during Skills 82 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

// int longgoal(){
//   delay(80);
//   intake_task = 2;
//   return 0;
// }

// int sololower(){
//   delay(100);
//   intake_task = 8;
//   return 0;
// }

int get_ball_clump_task_2(){
    wait_until([](){return chassis.drive_error < 10;}, 5, 1500);
    shovel.set_value(true);
    chassis.drive_max_voltage = 64;
    return 0;
}

void score_goal(int time, int goal_type){
    chassis.drive_with_voltage(-103, -103);
    delay(300);
    intake_task = goal_type;
    delay(100);
    chassis.drive_stop(MotorBrake::coast);
    delay(time);
    intake_task = 0;
    exit_somewhere_skills(false, 150);
}

void loader(bool left, bool north, bool keep_intake_running){
    double x_prep = left? 29.804 : 100;
    double y = north? 116 : 17;

    if(!(left && !north)){
        chassis.drive_to_point(x_prep, y);
    }

    if(keep_intake_running){
        intake_task = 1;
    }
    // chassis.drive_to_point(x_prep, y);
    shovel.set_value(true);
    //   chassis.turn_kp = 3.29;
    //   chassis.turn_settle_error = 1.85;
    chassis.turn_to_angle(left? 270 : 90); // loader
    if(keep_intake_running){
        intake_task = 1;
    }
    
    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    intake_task = 1;
    if((left && !north) || (!left && north)){
    chassis.wall_distance(chassis.WallSide::LEFT, 16.5, left? 270 : 90, 465, 50); // distance is relative
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, 16.5, left? 270 : 90, 480, 50);
    }
    intake_task = 1;
    chassis.drive_with_voltage(40, 40);
    delay(600);
    chassis.drive_with_voltage(15, 15);
    delay(1300);

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
    intake_task = 1;
    shovel.set_value(true);
    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    if((left && !north) || (!left && north)){
        chassis.wall_distance(chassis.WallSide::LEFT, 23, left? 270 : 90, 470, 50); // distance is relative
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, 23, left? 270 : 90, 530, 50);
    }
    chassis.drive_with_voltage(45, 45);
    // delay(2200);
    // delay(1000);
    // chassis.drive_stop(MotorBrake::brake);
    // delay(1500);
    delay(1000);
    delay(1200);
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
        intake_task = 1;
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
    double x_target = target_is_left? 21 : 120.4;
    // double x_inter1_turn = target_is_left? 20 : 120;
    // double y_intermediate = north? 125 : 9;
    double y_intermediate = north? 125 : 18;
    double y_goal = north? 116.5 : 22;//113 : 30

    default_constants();
    chassis.turn_to_angle(north? 0 : 180);
    chassis.drive_to_point(chassis.get_X_position(), y_intermediate);
    // default_constants();
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
    chassis.drive_to_point(chassis.get_X_position(), y_goal);

    chassis.turn_to_angle(target_is_left? 270 : 90);
}

/*
goal type: 
    2 = long goal
    3 = center low goal
    4 = center high goal
*/
void score_long_goal(bool left, bool north, bool far){
    double x_goal = left? 40 : 100;
    double y = north? 116.97 : 22.5;

    default_constants();
    chassis.drive_settle_error = 4;
    chassis.drive_timeout = 1000;
    if((left && !north) || (!left && north)){
        chassis.wall_distance(chassis.WallSide::LEFT, far? -21 : -21, left? 270 : 90, 470, 53);
    }
    else{
        chassis.wall_distance(chassis.WallSide::RIGHT, far? -21 : -21, left? 270 : 90, 530, 53);
    }

    // Task outtaketask(longgoal);// outtake 4 balls
    chassis.drive_with_voltage(-64, -64);
    delay(80);
    intake_task = 2;
    delay(220);
    intake_task = 2;
    delay(250);
    intake_task = 2;
    chassis.drive_stop(MotorBrake::brake);
    intake_task = 2;
    // shovel.set_value(false);
    // delay(100);
    delay(800);
    intake_task = 2;
    default_constants();
    // outtaketask.suspend();

    // chassis.turn_to_angle(left? 270 : 90);
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
    double left_dist = mm_to_inch(distance_sensorL.get()) + 3.25;
    double right_dist = mm_to_inch(distance_sensorR.get()) + 3.25;

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