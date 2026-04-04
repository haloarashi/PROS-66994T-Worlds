#include "main.h"

uint32_t hsv_to_rgb(float h, float s, float v, float time) {
    int i = int(h / 60) % 6;
    float f = h / 60 - i;
    float p = v * (1 - s);
    float q = v * (1 - f * s);
    float t = v * (1 - (1 - f) * s);

    float r, g, b;
    switch (i) {
        case 0: r = v; g = t; b = p; break;
        case 1: r = q; g = v; b = p; break;
        case 2: r = p; g = v; b = t; break;
        case 3: r = p; g = q; b = v; break;
        case 4: r = t; g = p; b = v; break;
        default:r = v; g = p; b = q; break;
    }
    
    // time = time / 100000; // scale speed
    // r = uint8_t((sin(time) * 0.5f + 0.5f) * 255);
    // g = uint8_t((sin(time + 2) * 0.5f + 0.5f) * 255);
    // b = uint8_t((sin(time + 4) * 0.5f + 0.5f) * 255);

    return (uint32_t(r * 255) << 16) | (uint32_t(g * 255) << 8) | uint32_t(b * 255);
}

uint32_t rgb_to_uint32(int r, int g, int b) {
    return (uint32_t(r) << 16) | (uint32_t(g) << 8) | uint32_t(b);
}

int overheat = 0;
int screen_time = 0;
void simple_screen_task(bool rainbow){
	while (true){
		pros::screen::erase();
    int overheat_threshold = 40;
    overheat = 0;

    if(chassis.DriveL.get_temperature(0) > overheat_threshold || chassis.DriveL.get_temperature(1) > overheat_threshold || chassis.DriveL.get_temperature(2) > overheat_threshold){
      pros::screen::print(TEXT_LARGE_CENTER, 10, "DRIVE_L OVERHEATING");
      overheat = 1;
    }
    if(chassis.DriveR.get_temperature(0) > overheat_threshold || chassis.DriveR.get_temperature(1) > overheat_threshold || chassis.DriveR.get_temperature(2) > overheat_threshold){
      pros::screen::print(TEXT_LARGE_CENTER, 10, "DRIVE_R OVERHEATING");
      overheat = 1;
	  }
    // if(intake_down.get_temperature() > overheat_threshold){
    //   pros::screen::print(TEXT_LARGE_CENTER, 10, "INTAKE_DOWN OVERHEATING");
    //   overheat = 2;
    // }
    // if(intake_mid.get_temperature() > overheat_threshold){
    //   pros::screen::print(TEXT_LARGE_CENTER, 10, "INTAKE_MID OVERHEATING");
    //   overheat = 3;
    // }
    // if(intake_up.get_temperature() > overheat_threshold){
    //   pros::screen::print(TEXT_LARGE_CENTER, 10, "INTAKE_UP OVERHEATING");
    //   overheat = 3;
    // }
    
    uint32_t flash_color;

    switch(overheat){
      case 1:
        flash_color = pros::c::COLOR_RED;
        break;

      case 2:
        flash_color = pros::c::COLOR_ORANGE;
        break;
      
      case 3:
        flash_color = pros::c::COLOR_GREEN;
        break;
      
      default:
        // pros::screen::set_pen(uint32_t((screen_time * 10) % 16777215));
        // pros::screen::set_eraser(uint32_t((screen_time * 10) % 16777215));
        float hue = fmod(screen_time  * 0.06, 360);
        // pros::screen::set_eraser(hsv_to_rgb(hue, 1, 1, screen_time));
        pros::screen::set_pen(pros::c::COLOR_BLACK);
        pros::screen::set_eraser(pros::c::COLOR_BLACK);
        pros::screen::fill_rect(1,1,480,240);
        pros::screen::set_pen(rainbow? hsv_to_rgb(hue, 1, 1, screen_time) : pros::c::COLOR_WHITE);
        break;
    }

    if(overheat != 0) {
      if(screen_time % 250 < 125){
        pros::screen::set_pen(pros::c::COLOR_BLACK);
        pros::screen::set_eraser(pros::c::COLOR_BLACK);
        pros::screen::fill_rect(1,1,480,240);
      }
      else{
        pros::screen::set_pen(flash_color);
        pros::screen::set_eraser(flash_color);
        pros::screen::fill_rect(1,1,480,240);
      }
      pros::screen::set_pen(pros::c::COLOR_WHITE);
    }
    
		pros::screen::print(TEXT_MEDIUM, 0, "X: %.2f,  Y: %.2f, Heading: %.2f", chassis.get_X_position(), chassis.get_Y_position(), chassis.get_absolute_heading());
    pros::screen::print(TEXT_MEDIUM, 1, "Pitch: %.2f, Roll: %.2f", chassis.Gyro.get_pitch(), chassis.Gyro.get_roll());
    pros::screen::print(TEXT_MEDIUM, 2, "Drive L pos: %.2f, Drive R pos: %.2f", chassis.DriveL.get_position(), chassis.DriveR.get_position());
		pros::screen::print(TEXT_MEDIUM, 3, "Intake temp: %.2f, Outtake temp: %.2f", intake.get_temperature(), outtake.get_temperature());
		pros::screen::print(TEXT_MEDIUM, 4, "DT L temp: %.2f, %.2f, %.2f", chassis.DriveL.get_temperature(0), chassis.DriveL.get_temperature(1), chassis.DriveL.get_temperature(2));
		pros::screen::print(TEXT_MEDIUM, 5, "DT R temp: %.2f, %.2f, %.2f", chassis.DriveR.get_temperature(0), chassis.DriveR.get_temperature(1), chassis.DriveR.get_temperature(2));
		pros::screen::print(TEXT_MEDIUM, 6, "Distance L (mm): %d, R (mm): %d", distance_sensorL.get(), distance_sensorR.get());
		pros::screen::print(TEXT_MEDIUM, 7, "DT L Torque (Nm): %.2f, %.2f, %.2f", chassis.DriveL.get_torque(0), chassis.DriveL.get_torque(1), chassis.DriveL.get_torque(2));
		pros::screen::print(TEXT_MEDIUM, 8, "DT R Torque (Nm): %.2f, %.2f, %.2f", chassis.DriveR.get_torque(0), chassis.DriveR.get_torque(1), chassis.DriveR.get_torque(2));

    pros::screen::print(TEXT_LARGE_CENTER, 10, "progress: %d", progress);
    
    // float avg_torque = (chassis.DriveL.get_torque(0) + chassis.DriveL.get_torque(1) + chassis.DriveL.get_torque(2) + chassis.DriveR.get_torque(0) + chassis.DriveR.get_torque(1) + chassis.DriveR.get_torque(2)) / 6.0;
    // printf("avg_torque: %.2f\n", avg_torque);

    printf("roll: %.2f\n", chassis.Gyro.get_roll());

    delay(50);
    screen_time += 50;
  }
}

void print_curvepoints(std::vector<CurvePoint> points){
  for(int i = 0; i < points.size(); i++){
    print_point(points[i].point, i);
    // TODO: also print drive_voltage, heading_max_voltage, and follow_distance
    // TODO: add a way to edit drive_voltage, heading_max_voltage, and follow_distance for each point
  }
}

void print_point(Point point, int line){
  screen::print(TEXT_MEDIUM, line, "Point: x %.1f, y %.1f, h %.0f, has_h: %s", point.x, point.y, point.heading, point.has_heading ? "true" : "false");
}

// vex screen is 480*240, with (0, 0) in the top left
void init_map(){
  screen::set_pen(pros::c::COLOR_WHITE);
  screen::draw_rect(120, 0, 360, 239);
}

void map_curvepoints(std::vector<CurvePoint> points){
  for(int i = 0; i < points.size(); i++){
    // game manual version
    int x = points[i].point.x / 140.41 * 120 + 120;
    int y = 120 - points[i].point.y / 140.41 * 120;

    // path.jerryio version
    // int x = points[i].point.x / 70 * 60 + 239;
    // int y = 60 - points[i].point.y / 70 * 60;

    screen::set_pen(pros::c::COLOR_RED);
    screen::draw_pixel(x, y);
  }
}

void update_map(){
  // game manual version
  int robot_x = chassis.get_X_position() / 140.41 * 120 + 120;
  int robot_y = 120 - chassis.get_Y_position() / 140.41 * 120;

  // path.jerryio version
  // int robot_x = chassis.get_X_position() / 70 * 60 + 239;
  // int robot_y = 60 - chassis.get_Y_position() / 70 * 60;
  
  screen::set_pen(pros::c::COLOR_YELLOW_GREEN);
  screen::draw_pixel(robot_x, robot_y);

  // printf("last_found_index: %d, L_voltage: %d, R_voltage: %dp\n", chassis.last_found_index, leftMotors.get_voltage(), rightMotors.get_voltage());
}

void map_task(){
  init_map();
  while(true){
    update_map();
    delay(50);
  }
}