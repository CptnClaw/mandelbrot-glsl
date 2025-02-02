#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaders.h"

#define MAX_SHADER_LENGTH 1024 * 10

void Shaders::uniform_double(const std::string &uniform_name, double f) const
{
    int unif_loc = glGetUniformLocation(id, uniform_name.c_str());
    glUniform1d(unif_loc, f);
}

void Shaders::uniform_float(const std::string &uniform_name, float f) const
{
    int unif_loc = glGetUniformLocation(id, uniform_name.c_str());
    glUniform1f(unif_loc, f);
}

void Shaders::uniform_modulation(const std::string &uniform_name) const
{
    double time = glfwGetTime();
    double modulation = (sin(time) + 1) / 2.0;
    uniform_float(uniform_name, modulation);
}

void Shaders::uniform_int(const std::string &uniform_name, int i) const
{
    int unif_loc = glGetUniformLocation(id, uniform_name.c_str());
    glUniform1i(unif_loc, i);
}


void Shaders::use() const
{
    glUseProgram(id);
}

Shaders::~Shaders()
{
    glDeleteProgram(id);
}

uint compile_shader(std::string shader_path, GLenum shader_type)
{
    int success;
    char compilation_errs[512];
    FILE *shader_file;
    char shader_txt[MAX_SHADER_LENGTH];

    // Read shader code
    shader_file = fopen(shader_path.c_str(), "r");
    if (!shader_file)
    {
        std::cout << "Cannot find shader file: " << shader_path << std::endl;
        return 0;
    }
    int filesize = fread(shader_txt, sizeof(char), MAX_SHADER_LENGTH, shader_file);
    shader_txt[filesize] = '\0';
    fclose(shader_file);
    const char *shader_src = shader_txt;

    // Compile shader
    uint shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &shader_src, nullptr);
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, compilation_errs);
        std::cout << "Error compiling shader (" << shader_path << "): " << std::endl;
        std::cout << compilation_errs << std::endl << std::endl;
        return 0;
    }
    return shader;
}

int build(uint *compiled_shaders, int num_shaders, bool &success)
{
    // Create program
    int linking_success;
    char compilation_errs[512];
    int id = glCreateProgram();
    
    // Attach shaders
    for (int i=0; i<num_shaders; i++)
    {
        glAttachShader(id, compiled_shaders[i]);
    }

    // Link and check for errors
    glLinkProgram(id);
    glGetProgramiv(id, GL_LINK_STATUS, &linking_success);
    success = true;
    if (!linking_success)
    {
        glGetProgramInfoLog(id, 512, nullptr, compilation_errs);
        std::cout << "Error linking shader program: " << std::endl;
        std::cout << compilation_errs << std::endl << std::endl;
        success = false;
    }
    return id;
}

Shaders::Shaders(const std::string &vertex_shader_path, const std::string &fragment_shader_path, bool &success)
{
    // Compile vertex and fragment shaders
    uint vertex_shader = compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
    uint fragment_shader = compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    if (0 == vertex_shader || 0 == fragment_shader)
    {
        success = false;
        return;
    }
    
    // Link program
    uint compiled[] = {vertex_shader, fragment_shader};
    id = build(compiled, 2, success);

    // Delete unnecessary resources
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

Shaders::Shaders(const std::string &vertex_shader_path, const std::string &geometry_shader_path,
                 const std::string &fragment_shader_path, bool &success)
{
    // Compile vertex, geometry, and fragment shaders
    uint vertex_shader = compile_shader(vertex_shader_path, GL_VERTEX_SHADER);
    uint geometry_shader = compile_shader(geometry_shader_path, GL_GEOMETRY_SHADER);
    uint fragment_shader = compile_shader(fragment_shader_path, GL_FRAGMENT_SHADER);
    if (0 == vertex_shader || 0 == geometry_shader || 0 == fragment_shader)
    {
        success = false;
        return;
    }
    
    // Link program
    uint compiled[] = {vertex_shader, geometry_shader, fragment_shader};
    id = build(compiled, 3, success);

    // Delete unnecessary resources
    glDeleteShader(vertex_shader);
    glDeleteShader(geometry_shader);
    glDeleteShader(fragment_shader);
}