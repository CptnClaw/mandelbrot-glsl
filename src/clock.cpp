#include <iostream>
#include <GLFW/glfw3.h>
#include "clock.h"

Clock::Clock() : prev_time(glfwGetTime()), prev_fps_print(prev_time), frame_counter(0)
{
    // Left empty intentionally
}

float Clock::tick()
{
    float cur_time = (float)glfwGetTime();

    if (cur_time - prev_fps_print > 1)
    {
        std::cout << "ms per frame: " << 1000.0 / (float)frame_counter << std::endl;
        prev_fps_print = cur_time;
        frame_counter = 0;
    }
    frame_counter++;

    float time_diff = cur_time - prev_time;
    prev_time = cur_time;
    return time_diff;
}