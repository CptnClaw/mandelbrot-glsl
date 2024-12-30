#include <iostream>
#include "callbacks.h"
#include "shaders.h"

#define PI 3.14159f

void error_callback(int err, const char *msg)
{
    std::cout << "Error " << err << ": " << msg << std::endl;
}

void modify_by_action(int action, float value, float &to_modify)
{
    if (action == GLFW_PRESS)   to_modify = value;
    if (action == GLFW_RELEASE) to_modify = 0;
    // else do nothing
}

bool is_wireframe = false;
float pan_x = 0.f, pan_y = 0.f, zoom = 0.f;

bool mouse_entered = false;
double last_mouse_x, last_mouse_y;
float mouse_sensitivity = .005f;
float scroll_sensitivity = .005f;

void key_callback(GLFWwindow *window, int key, [[maybe_unused]] int scancode, [[maybe_unused]] int action, [[maybe_unused]] int mods)
{
    switch (key)
    {
    case GLFW_KEY_Q:
    case GLFW_KEY_ESCAPE:
    case GLFW_KEY_CAPS_LOCK:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_1:
        // Toggle wireframe
        if (action == GLFW_PRESS)
        {
            if (is_wireframe)   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            else                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            is_wireframe = !is_wireframe;
        }
        break;
    case GLFW_KEY_W:
        modify_by_action(action, 1.f, pan_y);
        break;
    case GLFW_KEY_A:
        modify_by_action(action, -1.f, pan_x);
        break;
    case GLFW_KEY_S:
        modify_by_action(action, -1.f, pan_y);
        break;
    case GLFW_KEY_D:
        modify_by_action(action, 1.f, pan_x);
        break;
    case GLFW_KEY_EQUAL:
        modify_by_action(action, -1.f, zoom);
        break;
    case GLFW_KEY_MINUS:
        modify_by_action(action, 1.f, zoom);
        break;
    default:
        break;
    }
}

void fb_sz_callback([[maybe_unused]] GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}


void mouse_callback([[maybe_unused]] GLFWwindow *window, double x, double y)
{
    // Update selected pitch and yaw values according to mouse movements
    if (mouse_entered)
    {
        // *modifier_pitch += (float)(last_mouse_y - y) * mouse_sensitivity;
        // *modifier_yaw += (float)(x - last_mouse_x) * mouse_sensitivity;
    }
    
    // Remember current mouse coordinates
    mouse_entered = true;
    last_mouse_x = x;
    last_mouse_y = y;
}

void scroll_callback([[maybe_unused]] GLFWwindow *window, [[maybe_unused]] double xoffset, double yoffset)
{
    zoom -= yoffset * scroll_sensitivity;
}
