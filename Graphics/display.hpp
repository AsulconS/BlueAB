#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glManager.hpp"

class Display
{
private:
    GLFWwindow* window;

private:
    static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

public:
    Display(const unsigned int& width, const unsigned int& height, const std::string& name, unsigned int glVersion);
    virtual ~Display();

    void processInput();
    void processInput(float& value);
    void swapBuffers();
    bool active();
};

#endif // DISPLAY_H
