#include "shaders.h"
#include "canvas.h"
#include "clock.h"
#include "window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern float pan_x, pan_y, zoom;

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
    Shaders program("shaders/vertex.glsl", "shaders/fragment.glsl", shader_success);
    if (!shader_success)
    {
        return -1;
    }
    program.use();

    // Construct canvas to draw on
    Canvas canvas((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT);

    // Loop until the user closes the window
    Clock clock;
    while (window.next_frame_ready())
    {
        // Keep time since last frame 
        float delta_time = clock.tick();

        // Update canvas
        canvas.pan(pan_x * delta_time, pan_y * delta_time);
        canvas.zoom(zoom * delta_time);

        // Draw on canvas
        canvas.draw(program);
    }

    return 0;
}
