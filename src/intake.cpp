#include "main.h"

uint32_t clear_start_time = pros::millis();
uint32_t clear_time = 0;
uint32_t clog_time = 0;
uint32_t clog_start_time = pros::millis();
uint32_t unjam_attempt_time = 0;
uint32_t unjam_attempt_start_time = pros::millis();
uint32_t rest_time = 0;
uint32_t rest_start_time = pros::millis();

bool mid_stuck = false;

int mid_jam_time = 0;
// int unjam_attempt_time = 0;
// bool prev_was_unjamming = false;

int intake_status(){
  int intake_stats_count = 0;

  while(true){
    if(intake.get_torque() > 0.5){
      mid_jam_time += 10;
    }
    else{
      mid_jam_time = 0;
    }

    switch(intake_task){
      case 0: // stop intake
        brake_with_mode(intake, MotorBrake::brake);
        break;

      case 1: // start intake
        intake.move(127);
        brake_with_mode(outtake, MotorBrake::hold);
        break;

      case 2: // long goal out
        outtake_lift.set_value(true);
        intake.move(127);
        outtake.move(127);
        break;

      case 3: // rev intake
        intake.move(-127);
        outtake.move(-127);
        break;

      case 4: // upper goal out
        outtake_lift.set_value(false);
        intake.move(127);
        outtake.move(60);
        break;
      
      // case 5:
      //   intake_down.move(114);
      //   brake_with_mode(intake_mid, MotorBrake::coast);
      //   intake_up.brake();
      //   break;
      
      // case 6:{
      //   int start_time = pros::millis();
      //   int time_count = 0;
      //   while(time_count < 524){
      //     time_count = pros::millis() - start_time;
      //     if(time_count < 50){
            
      //     }
      //     else if(time_count < 325 + 50){
      //       intake_down.move(95);
      //       intake_mid.move(54);
      //     }
      //     else{
      //       intake_mid.brake();
      //       brake_with_mode(intake_up, MotorBrake::brake);
      //       intake_task = 1;
      //     }
      //   }
      //   break;}
        
      // case 7:{
      //   int start_time = pros::millis();
      //   int time_count = 0;
      //   while(time_count < 579){
      //     time_count = pros::millis() - start_time;
      //     if(time_count < 215){
      //       intake_down.move(95);
      //       intake_mid.move(54);
      //     }
      //     else if(time_count < 215 * 2){
      //       brake_with_mode(intake_up, MotorBrake::brake);
      //     }
      //     else{
      //       intake_mid.brake();
      //       intake_task = 1;
      //     }
      //   }
      //   break;}

      case 8: // low goal out (slowed)
        intake.move(-75);
        outtake.move(-127);
        break;
      // case 9: {
      //   int start_time = pros::millis();
      //   int time_count = 0;
      //   while(time_count < 1450 and !intake_task == 2 and !intake_task == 3 and !intake_task == 8 and !intake_task == 4){
      //     time_count = pros::millis() - start_time;
      //     if(time_count < 750){
      //       intake_down.move(89);
      //       intake_mid.move(-115);
      //       intake_up.move(-51);
      //     }
      //     else if(time_count > 750){
      //       intake_down.move(89);
      //       intake_mid.move(70);
      //       intake_up.move(-64);
      //     }
      //     else{
      //       intake_down.move(89);
      //       intake_mid.brake();
      //       intake_up.brake();
            
      //     }
      //   }
      //   break;}
      
      //   case 10: 
      //     intake_down.move(127);
      //     intake_mid.move(127);
      //     intake_up.move(70);
      //     break;
    }

    lift.set_value(intake_task == 3 || intake_task == 8);

    delay(10);
  }
  return 0;
}