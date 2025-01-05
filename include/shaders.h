#ifndef SHADERS_H_
#define SHADERS_H_

#include <string>

class Shaders
{
    public:
        // Reads, compiles and links shader program
        // Make sure to check last argument for any errors
        Shaders(const std::string &vertex_shader_path, 
                const std::string &fragment_shader_path, 
                bool &success);
        Shaders(const std::string &vertex_shader_path, 
                const std::string &geometry_shader_path, 
                const std::string &fragment_shader_path, 
                bool &success);

        // Frees resources
        ~Shaders();

        // Activate program
        void use() const;

        // Send uniform data to shaders
        void uniform_float(const std::string &uniform_name, float f) const;
        void uniform_double(const std::string &uniform_name, double f) const;
        void uniform_modulation(const std::string &uniform_name) const;
        void uniform_int(const std::string &uniform_name, int i) const;

    private:
        int id; // OpenGL program index
};

#endif // SHADERS_H_
