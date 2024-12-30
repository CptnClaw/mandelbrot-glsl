#include <iostream>
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include "canvas.h"

#define PAN_SPEED .5f
#define ZOOM_SPEED 1.f

Canvas::Canvas(float aspect_ratio) : aspect_ratio(aspect_ratio)
{
    // Initial position
    center_x = 0.0;
    center_y = 0.0;
    width = 4.0;

    // Define triangles
    float vertices[] = {
        -1.f, -1.f, 
         1.f, -1.f, 
        -1.f,  1.f, 
         1.f,  1.f
    };
    size_t stride = 2; // number of columns above
    uint indices[] = {
        0, 1, 2, 1, 2, 3
    };
    num_vertices = sizeof(indices) / sizeof(uint);

    // Create buffers on GPU
    glGenBuffers(1, &vbuf);
    glGenBuffers(1, &ibuf);
    glGenVertexArrays(1, &array_obj);

    // Copy vertices to GPU
    glBindVertexArray(array_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibuf);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    // Set vertex attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

Canvas::~Canvas()
{
    glDeleteVertexArrays(1, &array_obj);
    glDeleteBuffers(1, &ibuf);
    glDeleteBuffers(1, &vbuf);
}

void Canvas::draw(const Shaders &program) const
{
    // Calculate bounding box
    float left = center_x - width / 2.0;
    float right = left + width;
    float height = width / aspect_ratio;
    float down = center_y - height / 2.0;
    float up = down + height;

    // Send bounding box to fragment shader as uniforms
    program.uniform_float("left", left);
    program.uniform_float("right", right);
    program.uniform_float("down", down);
    program.uniform_float("up", up);

    // OpenGL draw calls
    glBindVertexArray(array_obj);
    glDrawElements(GL_TRIANGLES, num_vertices, GL_UNSIGNED_INT, 0);
}

void Canvas::pan(float x_dir, float y_dir)
{
    center_x = center_x + x_dir * PAN_SPEED * width;
    center_y = center_y + y_dir * PAN_SPEED * width;
}

void Canvas::zoom(float direction) 
{
    width = width * ZOOM_SPEED * (1+direction);
}