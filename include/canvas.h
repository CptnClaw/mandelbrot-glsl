#ifndef CANVAS_H_
#define CANVAS_H_

#include "shaders.h"

// A blank full-screen canvas to draw on by fragment shader
class Canvas
{
public:
    Canvas(float aspect_ratio);
    ~Canvas();
    
    // Draw frame to OpenGL buffer
    void draw(const Shaders &program) const;
    
    // Pan and zoom
    // Arguments should be -1.f, 0.f, or 1.f
    void pan(float x_dir, float y_dir);
    void zoom(float direction);

private:
    // Canvas size and location
    float center_x, center_y;
    float width;
    float aspect_ratio;

    // OpenGL stuff
    uint vbuf; // Index of vertices buffer on GPU
    uint ibuf; // Index of indices buffer on GPU
    uint array_obj; // Index of array object on GPU
    int num_vertices;
};

#endif // CANVAS_H_