#pragma once

int intake_status();

// extern uint32_t clear_start_time;
// extern uint32_t clear_time;
// extern uint32_t clog_time;
// extern uint32_t clog_start_time;
// extern uint32_t unjam_attempt_time;
// extern uint32_t unjam_attempt_start_time;
// extern uint32_t rest_time;
// extern uint32_t rest_start_time;

extern IntakeTask intake_task;

enum class IntakeTask{
    STOP,
    INTAKE,
    REVERSE,
    LOWER_GOAL_OUT,
    UPPER_GOAL_OUT,
    LONG_GOAL_OUT
};

// extern int mid_jam_time;