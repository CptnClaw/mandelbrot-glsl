#version 330 core

precision highp float;

uniform float left, right, up, down;
in vec2 frag_position;
out vec4 fragColor;

#define MAX_DEPTH 512


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

// Returns how many iterations it took seed to escape the polynomial iteration
// (or MAX_DEPTH if escape was never detected)
int mandelbrot(float seed_real, float seed_imaginary)
{
    // Start at 0+i0
    float val_real = 0;
    float val_imaginary = 0;

    for (int i = 0; i < MAX_DEPTH; i++)
    {
        // Square the real and imaginary parts
        float val_real2 = val_real * val_real;
        float val_imaginary2 = val_imaginary * val_imaginary;

        // Check if norm squared is larger than 4, meaning escape
        if (val_real2 + val_imaginary2 >= 4.0)
        {
            return i;
        }

        // Not escaped, calculate next polynomial iteration
        float val_real_next = seed_real + val_real2 - val_imaginary2;
        val_imaginary = seed_imaginary + 2.0 * (val_real * val_imaginary);
        val_real = val_real_next;
    }
    return MAX_DEPTH;
}

void main()
{
    float seed_real = convert_range(frag_position.x, -1.0, 1.0, left, right);
    float seed_imaginary = convert_range(frag_position.y, -1.0, 1.0, down, up);
    int depth = mandelbrot(seed_real, seed_imaginary);
    float ratio = float(depth) / float(MAX_DEPTH);
    fragColor = vec4(vec3(1 - ratio), 1.0);
}
