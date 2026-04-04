class Drive;
extern Drive chassis;

void square(float side_length);

// Created during Skills 114 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

void red_parking_zone();
void sideways_parking_zone(bool left, bool red);
void one_center_block_then_score(bool left, bool north);
void ball_clump(bool left);

int soloupper();
void sideways_parking_zone_tracking_task(bool add_extra_exit_condition);
extern int progress;

// Created during Skills 82 vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

int longgoal();

void park();
void fwd_park();

void loader(bool left, bool north, bool keep_intake_running = true);
void get_loader(bool wall_is_left, double dist_from_loader = 0);
void set_coordinates_start(bool left, bool face_north);

void score_goal(int time, IntakeTask goal_type);
void score_long_goal(bool left, bool north, bool far);
void go_to_other_end_of_long_goal(bool target_is_left, bool north);
void exit_somewhere_skills(bool drive_fwd, int time, bool reset_intake = true);

void loader_from_goal(bool left, bool north);

/* @param corner
    1 = left north (0, 140.41)
    2 = right north (140.41, 140.41)
    3 = right south (140.41, 0)
    4 = left south (0, 0)

    I didn't write all corners! Add corners as needed. 
*/
void calibrate_coordinates(int corner, bool use_left_sensor, bool use_left_right_wall);

int sololower();

int ball_clump_shovel_task();