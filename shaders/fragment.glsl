#version 460 core

precision highp float;
precision highp int;

uniform double left, right, up, down;
in vec2 frag_position;
out vec4 fragColor;

#define MAX_DEPTH 512

// // Custom implementation of a fixed-point number
// // Has 1 bit for signed, 2 bits for the integer part,
// // and 
// struct fixedpt
// {
//     int f;
// };

// // Fixed point arithmetic 
// fixedpt add(fixedpt a, fixedpt b);
// fixedpt sub(fixedpt a, fixedpt b);
// fixedpt mul(fixedpt a, fixedpt b);


double convert_range(double value, double old_start, double old_end, double new_start, double new_end)
{
    // Start in range [old_start, old_end]
    // Normalize to [0, old_end - old_start]
    double result = value - old_start; 
    
    // Normalize to [0, 1]
    result = result / (old_end - old_start);
    
    // Normalize to [0, new_end - new_start]
    result = result * (new_end - new_start);

    // Finally, return in range [new_start, new_end]
    return result + new_start;
}

// Returns how many iterations it took seed to escape the polynomial iteration
// (or MAX_DEPTH if escape was never detected)
int mandelbrot(double seed_real, double seed_imaginary)
{
    // Start at 0+i0
    double val_real = 0;
    double val_imaginary = 0;

    for (int i = 0; i < MAX_DEPTH; i++)
    {
        // Square the real and imaginary parts
        double val_real2 = val_real * val_real;
        double val_imaginary2 = val_imaginary * val_imaginary;

        // Check if norm squared is larger than 4, meaning escape
        if (val_real2 + val_imaginary2 >= 4.0)
        {
            return i;
        }

        // Not escaped, calculate next polynomial iteration
        double val_real_next = seed_real + val_real2 - val_imaginary2;
        val_imaginary = seed_imaginary + 2.0 * (val_real * val_imaginary);
        val_real = val_real_next;
    }
    return MAX_DEPTH;
}

void main()
{
    double seed_real = convert_range(frag_position.x, -1.0, 1.0, left, right);
    double seed_imaginary = convert_range(frag_position.y, -1.0, 1.0, down, up);
    int depth = mandelbrot(seed_real, seed_imaginary);
    double ratio = double(depth) / double(MAX_DEPTH);
    fragColor = vec4(vec3(1 - ratio), 1.0);
}
