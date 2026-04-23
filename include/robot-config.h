#pragma once
#include "Template/api.h"

using namespace pros;

extern Drive chassis;

extern IMU inertial;
extern Rotation fwd_tracker;
extern Rotation sideways_tracker;

extern MotorGroup leftMotors;
extern MotorGroup rightMotors;

extern Motor intake;
extern Motor outtake;

extern adi::DigitalOut roof;
extern adi::DigitalOut lift;
extern adi::DigitalOut outtake_lift;
extern adi::DigitalOut claw;
extern adi::DigitalOut upper_descore;
extern adi::DigitalOut shovel;

extern Distance distance_sensorL;
extern Distance distance_sensorR;

extern lemlib::Drivetrain drivetrain;
extern lemlib::OdomSensors sensors;
extern lemlib::ControllerSettings lateral_controller;
extern lemlib::ControllerSettings angular_controller;
extern lemlib::Chassis chassis_lemlib;

void default_constants();
void init();

// Your motors, sensors, etc. should go here.  Below are examples
// inline pros::adi::DigitalIn limit_switch('A');