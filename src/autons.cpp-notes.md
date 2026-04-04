# Doesn't use Odometry
- `sideways_parking_zone()`
- `loader_from_goal()`
- `exit_somewhere_skills()`
- `fwd_park()`
- `go_to_other_end_of_long_goal()`
- `ball_clump()`
- `loader()`
- `score_long_goal()`
- `one_center_block_then_score()` - Odometry should be fine since it's right after coordinate reset, but it is also right after drive_with_voltage(127, 127), so no. 

# Uses Odometry
None :(