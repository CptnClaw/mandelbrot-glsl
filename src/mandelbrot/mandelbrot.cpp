#include <iostream>
#include <glad/glad.h>
#include "shaders.h"
#include "canvas.h"
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
    Shaders program("shaders/vertex_passthrough.glsl", "shaders/fragment_mandelbrot.glsl", shader_success); 
    if (!shader_success)
    {
        return -1;
    }
    program.use();

    // Construct canvas to draw on
    Canvas canvas((double)WINDOW_WIDTH / (double)WINDOW_HEIGHT);

    // Loop until the user closes the window
    Clock clock;
    while (window.next_frame_ready())
    {
        // Keep time since last frame 
        float delta_time = clock.tick();

        // Update canvas
        canvas.pan(pan_x * delta_time, pan_y * delta_time);
        canvas.zoom(zoom * delta_time);
        program.uniform_float("color_phase", scroll);
        program.uniform_int("max_depth", 1 << keynum); // pow(2,keynum)

        // Draw on canvas
        canvas.draw(program);
    }

    return 0;
}
