# Doesn't use odometry
- `sideways_parking_zone()`
- `loader_from_goal()`
- `exit_somewhere_skills()`
- `fwd_park()`

# Uses odometry
- `one_center_block_then_score()` - Should be fine since it's right after coordinate reset
- `ball_clump()`
- `loader()`
- `go_to_other_end_of_long_goal()`
- `score_long_goal()`