#include <iostream>
#include <glad/glad.h>
#include "shaders.h"
#include "canvas.h"
#include "clock.h"
#include "window.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

extern double pan_x, pan_y, zoom;

void query_precision(GLenum precisionType)
{
    int ret_range[2];
    int ret_precision;
    glGetShaderPrecisionFormat(GL_FRAGMENT_SHADER, precisionType, ret_range, &ret_precision);
    std::cout << "min: " << ret_range[0] << ", max: " << ret_range[1] << ", precision: " << ret_precision << std::endl;
}

int main()
{
    // Open window and initialize OpenGL
    bool init_success;
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, init_success);
    if (!init_success)
    {
        return -1;
    }
    
    // Query variables precision in fragment shader
    query_precision(GL_MEDIUM_FLOAT);
    query_precision(GL_HIGH_FLOAT);
    query_precision(GL_MEDIUM_INT);
    query_precision(GL_HIGH_INT);

    // Build shaders programs
    bool shader_success;
    Shaders program("shaders/vertex.glsl", "shaders/fragment.glsl", shader_success);
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

        // Draw on canvas
        canvas.draw(program);
    }

    return 0;
}
