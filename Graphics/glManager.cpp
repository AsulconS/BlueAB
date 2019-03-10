#include "glManager.h"

bool GLManager::gladInitialized = false;
bool GLManager::glfwInitialized = false;

unsigned int GLManager::windowInstances = 0;

void* GLManager::windowContextPtr = NULL;

void GLManager::error_callback(int error, const char* description)
{
    std::cerr << "GLFW crashed:\nError N. " << error << ": " << description << std::endl;
}

void GLManager::initGlad()
{
    if(!GLManager::gladInitialized && GLManager::glfwInitialized)
    {
        // glad: load all OpenGL function pointers
        // ---------------------------------------
        if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            std::cerr << "Failed to initialize glad" << std::endl;
            if(GLManager::glfwInitialized) glfwTerminate();
            throw;
        }
        GLManager::gladInitialized = true;
        std::cout << "glad initialized successfully" << std::endl;
        return;
    }
    std::cerr << "glad already initialized" << std::endl;
}

void GLManager::initGLFW()
{
    if(!GLManager::glfwInitialized && !GLManager::gladInitialized)
    {
        // glfw: initialize and configure
        // ------------------------------
        if(!glfwInit())
        {
            std::cerr << "Failed to initialize GLFW" << std::endl;
            throw;
        }
        glfwSetErrorCallback(GLManager::error_callback);
        GLManager::glfwInitialized = true;
        std::cout << "GLFW initialized successfully" << std::endl;
        return;
    }
    std::cerr << "GLFW already initialized" << std::endl;
}

void GLManager::hardware_specifications_debug()
{
    GLint nrAttributes;
    GLint majorVersion;
    GLint minorVersion;
    const char* glslVersion;

    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrAttributes);
    glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
    glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
    glslVersion = reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION));

    std::cout << "Window instances: " << GLManager::windowInstances << std::endl;

    std::cout << "Hardware Specifications Debug: " << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
    std::cout << "Maximum nr of vertex attributes supported: " << nrAttributes << std::endl;
    std::cout << "GL Major version: " << majorVersion << std::endl;
    std::cout << "GL Minor version: " << minorVersion << std::endl;
    std::cout << "GLSL Version: " << glslVersion << std::endl;
    std::cout << "----------------------------------------------\n" << std::endl;
}
