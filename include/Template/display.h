#pragma once
#include "main.h"
using namespace pros;

uint32_t hsv_to_rgb(float h, float s, float v);
uint32_t rgb_to_uint32(int r, int g, int b);

void simple_screen_task(bool rainbow);

void print_curvepoints(std::vector<CurvePoint> points);
void print_point(Point point, int line);

void init_map();
void map_curvepoints(std::vector<CurvePoint> points);
void update_map();
void map_task();