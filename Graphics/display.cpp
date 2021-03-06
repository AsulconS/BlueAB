#include "display.hpp"

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void Display::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

Display::Display(const unsigned int& width, const unsigned int& height, const std::string& name, unsigned int glVersion)
{
    // glfw: init GLFW
    // ---------------
    if(!GLManager::isGLFWInitialized()) GLManager::initGLFW();

    if(!GLManager::windowInstances)
    {
        // glfw: window hints
        // ------------------
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glVersion);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // For Mac OS X Compatibility
        #endif
        // glfw: window creation
        // ---------------------
        window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
        if(window == NULL)
        {
            std::cerr << "Failed to create GLFW Window" << std::endl;
            glfwTerminate();
            throw;
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, Display::framebuffer_size_callback);

        GLManager::initGlad();

        GLManager::windowContextPtr = window;
        GLManager::windowInstances++;
    }
    else
    {
        window = static_cast<GLFWwindow*>(GLManager::windowContextPtr);
        GLManager::windowInstances++;
        std::cerr << "DISPLAY CREATION ERROR:\n";
        std::cerr << "------------------------------------------------\n";
        std::cerr << "Could not create another window instance\n";
        std::cerr << "This instance owns to the same previous instance\n";
        std::cerr << "------------------------------------------------\n" << std::endl;
    }
    
}

Display::~Display()
{
    if(GLManager::windowInstances == 1)
    {
        --GLManager::windowInstances;
        // glfw: terminate, clearing all previously allocated GLFW resources
        // -----------------------------------------------------------------
        glfwTerminate(); std::cout << "Worked Successfully! GLFW terminated OK" << std::endl;
    }
    else
        --GLManager::windowInstances;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void Display::processInput()
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
}

void Display::processInput(float& value)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        value += 0.0001f;
        if(value >= 1.0f)
            value = 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        value -= 0.0001f;
        if(value <= 0.0f)
            value = 0.0f;
    }
}

void Display::processInput(glm::vec3& cameraPos, glm::vec3& cameraDir, glm::vec3& cameraUp, float& yaw, float cameraSpeed, float deltaTime)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        cameraPos += deltaTime * cameraSpeed * cameraDir;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        cameraPos -= deltaTime * cameraSpeed * cameraDir;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        cameraPos -= deltaTime * cameraSpeed * glm::normalize(glm::cross(cameraDir, cameraUp));
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        cameraPos += deltaTime * cameraSpeed * glm::normalize(glm::cross(cameraDir, cameraUp));
    }

    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        yaw += deltaTime * cameraSpeed / 4.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        yaw -= deltaTime * cameraSpeed / 4.0f;
    }
    cameraDir.x = -sin(yaw);
    cameraDir.z = -cos(yaw);
    std::cout << "x: " << cameraDir.x << " | z: " << cameraDir.z << std::endl;
}

// ---------------------------------------------------------------------------------------------------------

void Display::swapBuffers()
{
    glfwSwapBuffers(window);
}

bool Display::active()
{
    return !glfwWindowShouldClose(window);
}
