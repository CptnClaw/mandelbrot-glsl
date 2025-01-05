#version 460 core

uniform int colormode;
uniform float colorphase;
in float derivative;
out vec4 fragColor;

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

void main()
{
    fragColor = vec4(1.0, 1.0, 1.0, 0.0);
    if (colormode == 1)
    {
        vec4 color1 = vec4(.0, 1.0, 0.0, 1.0);
        vec4 color2 = vec4(0.0, 0.0, 1.0, 1.0);
        fragColor = mix(color1, color2, derivative);
    }
    else if (colormode == 2)
    {
        fragColor = HSL2RGB(mod(colorphase + derivative, 1.0), 0.9, 0.5);
    }
}
