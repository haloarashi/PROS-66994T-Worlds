#include "main.h"
#include "Template/auton-selector.h"

AutonRoutine::AutonRoutine(std::function<void()> auton_routine, uint32_t bt_color, int row, int column):
    auton_routine(auton_routine), 
    type(AutonType::UNDEFINED), 
    bt_color(bt_color), 
    row(row), 
    column(column)
{}

AutonRoutine::AutonRoutine(std::function<void()> auton_routine, AutonRoutine::AutonType type, uint32_t bt_color, int row, int column):
    auton_routine(auton_routine), 
    type(type), 
    bt_color(bt_color), 
    row(row), 
    column(column)
{}

void draw_btn(AutonRoutine routine, int index, AutonRoutine::AutonType type, int btn_width, int btn_height, int gap){
    // rectangle
    uint32_t left_btn_color = pros::c::COLOR_GREEN;
    uint32_t solo_btn_color = pros::c::COLOR_PURPLE;
    uint32_t right_btn_color = pros::c::COLOR_YELLOW;
    uint32_t default_btn_color = pros::c::COLOR_WHITE;

    switch(type){
        case AutonRoutine::AutonType::LEFT: 
            pros::screen::set_pen(left_btn_color);
            break;
        
        case AutonRoutine::AutonType::SOLO: 
            pros::screen::set_pen(solo_btn_color);
            break;
        
        case AutonRoutine::AutonType::RIGHT: 
            pros::screen::set_pen(right_btn_color);
            break;
        
        default: 
            pros::screen::set_pen(default_btn_color);
            break;
    }
    
    int row = index % 2;
    int column = index / 2;

    int x0 = (btn_width + gap) * (row - 1);
    int y0 = (btn_height + gap) * (column - 1);

    pros::screen::draw_rect(x0, y0, x0 + btn_width, y0 + btn_height);

    // text
    switch(type){
        case AutonRoutine::AutonType::LEFT: 
            pros::screen::set_pen(pros::c::COLOR_WHITE);
            pros::screen::set_eraser(left_btn_color);
            break;
            
            case AutonRoutine::AutonType::SOLO: 
            pros::screen::set_pen(pros::c::COLOR_WHITE);
            pros::screen::set_eraser(solo_btn_color);
            break;
            
            case AutonRoutine::AutonType::RIGHT: 
            pros::screen::set_pen(pros::c::COLOR_WHITE);
            pros::screen::set_eraser(right_btn_color);
            break;
            
            default: 
            pros::screen::set_pen(pros::c::COLOR_BLACK);
            pros::screen::set_eraser(default_btn_color);
            break;
    }

    // pros::screen::print(TEXT_MEDIUM, )
}

void idk1(std::vector<AutonRoutine> left_routines, std::vector<AutonRoutine> solo_routines, std::vector<AutonRoutine> right_routines){
    // draw buttons

    for(AutonRoutine l : left_routines){

    }

    // int width = 480 / columns;
    // int height = 240 / rows;
    // for(int x = 0; x < 480 - width; x += width){
    //     for(int y = 0; y < 240 - rows; y += height){
    //         int hue = ;
    //         pros::screen::set_pen();
    //         pros::screen::draw_rect(x, y, x + width, y + height);
    //     }
    // }
}

void draw_buttons(std::vector<AutonRoutine> routines, int row_limit){
    // // determine max row and column specifications in routines
    // int max_row = -1;
    // int max_column = -1;
    // for(AutonRoutine routine : routines){
    //     max_row = std::max(routine.row, max_row);
    //     max_column = std::max(routine.column, max_column);
    // }

    // give all elements a column and row


    // // determine how many rows and columns to draw
    // int columns = std::max(column_limit, max_column);
    // columns = std::min(columns, (int)routines.size());

    // int rows = std::max(row_limit, max_row);
    // rows = std::min(rows, (int)routines.size());
    
    // // draw buttons
    // int width = 480 / columns;
    // int height = 240 / rows;
    // for(int x = 0; x < 480 - width; x += width){
    //     for(int y = 0; y < 240 - rows; y += height){
    //         int hue = ;
    //         pros::screen::set_pen();
    //         pros::screen::draw_rect(x, y, x + width, y + height);
    //     }
    // }
}

// // vex screen is 480*240, with (0, 0) in the top left
// void auton_selector(int rows, int columns){
//     int width = 480 / columns;
//     int height = 240 / rows;
    
//     for(int x = 0; x < 480 - width; x += width){
//         for(int y = 0; y < 240 - rows; y += height){
//             int hue = ;
//             pros::screen::set_pen();
//             pros::screen::draw_rect(x, y, x + width, y + height);
//         }
//     }
// }