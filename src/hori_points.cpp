#include <iostream>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "hori_points.h"

#define PAN_SPEED .5f
#define ZOOM_SPEED 1.f

HoriPoints::HoriPoints(int num_points, float ycoord) : num_points(num_points)
{
    // Define triangles
    size_t stride = 2;
    int buffer_len = num_points * (int)stride;
    float *vertices = new float[buffer_len];
    for (int i=0; i<buffer_len; i+=stride)
    {
        vertices[i] = ((float)i / (buffer_len)) * 2.0 - 1.0; // distribute evenly between -1.0 and 1.0
        vertices[i+1] = ycoord;
    }

    // Create buffers on GPU
    glGenBuffers(1, &vbuf);
    glGenVertexArrays(1, &array_obj);

    // Copy vertices to GPU
    glBindVertexArray(array_obj);
    glBindBuffer(GL_ARRAY_BUFFER, vbuf);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * buffer_len, vertices, GL_STATIC_DRAW);
    
    // Set vertex attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

HoriPoints::~HoriPoints()
{
    glDeleteVertexArrays(1, &array_obj);
    glDeleteBuffers(1, &vbuf);
}

void HoriPoints::draw([[maybe_unused]] const Shaders &program) const
{
    // OpenGL draw calls
    glBindVertexArray(array_obj);
    glDrawArrays(GL_POINTS, 0, num_points);
}