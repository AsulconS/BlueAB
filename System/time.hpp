#ifndef TIME_H
#define TIME_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Time
{
    static float deltaTime = 0.0f;
    static float lastFrame = 0.0f;
    static float currentFrame = 0.0f;

    float getDeltaTime()
    {
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        return deltaTime;
    }
}

#endif // TIME_H

