#pragma once

class AutonRoutine{
    public:
        std::function<void()> auton_routine;
        uint32_t bt_color;
        int row;
        int column;

        enum class AutonType{
            LEFT, 
            RIGHT, 
            SOLO, 
            UNDEFINED
        };

        AutonType type;

        AutonRoutine(std::function<void()> auton_routine, uint32_t bt_color, int row = -1, int column = -1);
        AutonRoutine(std::function<void()> auton_routine, AutonType type, uint32_t bt_color, int row = -1, int column = -1);
};

void auton_selector(int rows = 2);