#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
private:
    enum
    {
        VERTEX_SHADER,
        FRAGMENT_SHADER,
        NUM_SHADERS
    };

    enum
    {
        COMPILATION,
        LINKING
    };

private:
    GLuint ID;
    GLuint shaders[NUM_SHADERS];

private:
    std::string loadShader(const std::string& shaderFilename);
    GLuint createShader(const std::string& shaderFilename, GLenum type);
    void checkCompileErrors(GLuint shader, bool type);

public:
    Shader(const std::string& shaderFilename);
    virtual ~Shader();

    inline GLuint getProgramHandler() { return this->ID; }

    void use();
    void setBool(const std::string& name, bool value);
    void setInt(const std::string& name, int value);
    void setFloat(const std::string& name, float value);

    void set2Float(const std::string& name, float v0, float v1);
    void set3Float(const std::string& name, float v0, float v1, float v2);
    void set4Float(const std::string& name, float v0, float v1, float v2, float v3);

    void setMat4(const std::string& name, bool transposed, glm::mat4& m0);
};

#endif // SHADER_H
