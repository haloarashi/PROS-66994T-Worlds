#pragma once

int intake_jam();
int intake_status();

extern uint32_t clear_start_time;
extern uint32_t clear_time;
extern uint32_t clog_time;
extern uint32_t clog_start_time;
extern uint32_t unjam_attempt_time;
extern uint32_t unjam_attempt_start_time;
extern uint32_t rest_time;
extern uint32_t rest_start_time;

extern int intake_task;

extern int mid_jam_time;

// extern int attempt_unjam_time;