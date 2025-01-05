#version 460 core

uniform float range_start;
uniform float range_end;
uniform float seed;
uniform int iterations_before;
uniform int iterations_after;

layout (points) in;
// layout (line_strip, max_vertices=200) out;
layout (points, max_vertices=250) out;

float convert_range(float value, float old_start, float old_end, float new_start, float new_end)
{
    // Start in range [old_start, old_end]
    // Normalize to [0, old_end - old_start]
    float result = value - old_start; 
    
    // Normalize to [0, 1]
    result = result / (old_end - old_start);
    
    // Normalize to [0, new_end - new_start]
    result = result * (new_end - new_start);

    // Finally, return in range [new_start, new_end]
    return result + new_start;
}

float logistic_map(float r, float val)
{
    return r * val * (1.0 - val);
}

void main()
{
    float r = convert_range(gl_in[0].gl_Position.x, -1.0, 1.0, range_start, range_end);
    float val = seed;
    for (int i=0; i<iterations_before; i++)
    {
       val = logistic_map(r, val); 
    }
    
    for (int i=0; i<iterations_after; i++)
    {
       val = logistic_map(r, val); 
       gl_Position = gl_in[0].gl_Position + vec4(0.0, val, 0.0, 0.0);
       EmitVertex();
       EndPrimitive();
    }
}