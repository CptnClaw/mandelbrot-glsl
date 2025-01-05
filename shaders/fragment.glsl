#version 460 core

// precision highp float;
// precision highp int;

uniform double left, right, up, down;

in vec2 frag_position;
out vec4 fragColor;

#define MAX_DEPTH 256


vec4 HSL2RGB(float h, float s, float l) 
{
    float chroma = (1.0 - abs(2.0 * l - 1.0)) * s;
    float x = chroma * (1.0 - abs(mod(h * 6.0, 2.0) - 1.0));
    vec3 added_lightness = vec3(l - 0.5 * chroma);

    vec4 rgb = vec4(0.0);
    rgb += (int(h < 1.0 / 6.0) * vec4(chroma, x, 0.0, 1.0));
    rgb += (int(1.0 / 6.0 <= h && h < 2.0 / 6.0) * vec4(x, chroma, 0.0, 1.0));
    rgb += (int(2.0 / 6.0 <= h && h < 3.0 / 6.0) * vec4(0.0, chroma, x, 1.0));
    rgb += (int(3.0 / 6.0 <= h && h < 4.0 / 6.0) * vec4(0.0, x, chroma, 1.0));
    rgb += (int(4.0 / 6.0 <= h && h < 5.0 / 6.0) * vec4(x, 0.0, chroma, 1.0));
    rgb += (int(5.0 / 6.0 <= h) * vec4(chroma, 0.0, x, 1.0));
    return rgb + vec4(added_lightness, 0.0);
}

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
// The iteration count is "corrected" to enable smooth coloring, see: http://linas.org/art-gallery/escape/smooth.html
float mandelbrot(double seed_real, double seed_imaginary)
{
    // Start at 0+i0
    double val_real = 0;
    double val_imaginary = 0;

    for (int i = 0; i < MAX_DEPTH; i++)
    {
        // Square the real and imaginary parts
        double val_real2 = val_real * val_real;
        double val_imaginary2 = val_imaginary * val_imaginary;
        double cross = val_real * val_imaginary;
        double magnitude2 = val_real2 + val_imaginary2;

        // Check if norm squared is larger than 4, meaning escape
        if (magnitude2 >= 4.0)
        {
            return float(i) + 1.0 - log(log(sqrt(float(magnitude2))) / log(2.0));
        }

        // Not escaped, calculate next polynomial iteration
        val_real = seed_real + val_real2 - val_imaginary2;
        val_imaginary = seed_imaginary + cross + cross;
    }
    return float(MAX_DEPTH);
}

void main()
{
    double seed_real = convert_range(frag_position.x, -1.0, 1.0, left, right);
    double seed_imaginary = convert_range(frag_position.y, -1.0, 1.0, down, up);
    float iterations = mandelbrot(seed_real, seed_imaginary);
    
    fragColor = vec4(0.0, 0.0, 0.0, 1.0);
    if (iterations < float(MAX_DEPTH))
    {
        float hue = mod(iterations / float(MAX_DEPTH) * 1.1, 1.0); // Wrap hue around 0-1 range
        float saturation = 0.9;
        float lightness = 0.5;
        fragColor = HSL2RGB(hue, saturation, lightness);
    }
}
