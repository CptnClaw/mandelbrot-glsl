#ifndef HORI_POINTS_H_
#define HORI_POINTS_H_

#include "shaders.h"

// A bunch of points lined up horizontally to be manipulated by geometry shader
class HoriPoints
{
public:
    HoriPoints(int num_points, float ycoord);
    ~HoriPoints();
    
    // Draw frame to OpenGL buffer
    void draw(const Shaders &program) const;
    
private:
    int num_points;

    // OpenGL stuff
    uint vbuf; // Index of vertices buffer on GPU
    uint array_obj; // Index of array object on GPU
};

#endif // HORI_POINTS_H_