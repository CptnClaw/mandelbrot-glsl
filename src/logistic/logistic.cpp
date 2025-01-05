#include <iostream>
#include <glad/glad.h>
#include "shaders.h"
#include "hori_points.h"
#include "clock.h"
#include "window.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 900

extern double pan_x, pan_y, zoom;
extern float scroll;
extern int keynum;

int main()
{
    // Open window and initialize OpenGL
    bool init_success;
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, init_success);
    if (!init_success)
    {
        return -1;
    }
    
    // Build shaders programs
    bool shader_success;
    Shaders program("shaders/vertex_simple.glsl",
                    "shaders/geometry_logistic.glsl",
                    "shaders/fragment_simple.glsl",
                    shader_success);
    if (!shader_success)
    {
        return -1;
    }
    program.use();

    // Construct horizontal points to manipulate and draw
    HoriPoints pts(3000, -.5f);

    // Loop until the user closes the window
    Clock clock;
    float range_center = 1.f;
    float width = 6.f;
    keynum = 1;
    while (window.next_frame_ready())
    {
        // Keep time since last frame 
        float delta_time = clock.tick();
        
        range_center += pan_x * delta_time;
        width *= ((zoom * delta_time) + 1);

        // Draw points
        float noise = (float)rand() / (float)(RAND_MAX);
        noise /= 100.f;
        program.uniform_float("range_start", range_center - (width / 2.f));
        program.uniform_float("range_end", range_center + (width / 2.f));
        program.uniform_float("seed", .2f + noise);
        program.uniform_int("iterations_before", 300);
        program.uniform_int("iterations_after", 250);
        program.uniform_int("colormode", keynum);
        program.uniform_int("colorphase", scroll);
        pts.draw(program);
    }

    return 0;
}
