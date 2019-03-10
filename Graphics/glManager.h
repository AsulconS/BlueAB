#ifndef GL_MANAGER_H
#define GL_MANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <string>
#include <iostream>

// Singleton GL Manager Class
class GLManager
{
private:
    static bool gladInitialized;
    static bool glfwInitialized;

private:
    static void error_callback(int error, const char* description);

public:
    static unsigned int windowInstances;
    static void* windowContextPtr;

public:
    static void initGlad();
    static void initGLFW();

    static inline bool isGladInitialized() { return GLManager::gladInitialized; }
    static inline bool isGLFWInitialized() { return GLManager::glfwInitialized; }

    static void hardware_specifications_debug();
};

#endif // GL_MANAGER_H
