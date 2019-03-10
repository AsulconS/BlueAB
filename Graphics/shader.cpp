#include "shader.h"

Shader::Shader(const std::string& shaderFilename)
{
    shaders[VERTEX_SHADER] = createShader(shaderFilename + ".vs", GL_VERTEX_SHADER);
    shaders[FRAGMENT_SHADER] = createShader(shaderFilename + ".fs", GL_FRAGMENT_SHADER);

    ID = glCreateProgram();
    glAttachShader(ID, shaders[VERTEX_SHADER]);
    glAttachShader(ID, shaders[FRAGMENT_SHADER]);
    glLinkProgram(ID);
    checkCompileErrors(ID, LINKING);
}

Shader::~Shader()
{
    for(size_t i = 0; i < NUM_SHADERS; ++i)
    {
        glDetachShader(ID, shaders[i]);
        glDeleteShader(shaders[i]);
    }
    glDeleteProgram(ID);
    std::cout << "Shader Deleted Successfully" << std::endl;
}

void Shader::setBool(const std::string& name, bool value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value)
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value)
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::set2Float(const std::string& name, float v0, float v1)
{
    glUniform2f(glGetUniformLocation(ID, name.c_str()), v0, v1);
}

void Shader::set3Float(const std::string& name, float v0, float v1, float v2)
{
    glUniform3f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2);
}

void Shader::set4Float(const std::string& name, float v0, float v1, float v2, float v3)
{
    glUniform4f(glGetUniformLocation(ID, name.c_str()), v0, v1, v2, v3);
}

void Shader::setMat4(const std::string& name, bool transposed, glm::mat4& m0)
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, transposed, glm::value_ptr(m0));
}

void Shader::use()
{
    glUseProgram(ID);
}

GLuint Shader::createShader(const std::string& shaderFilename, GLenum type)
{
    GLuint shader = glCreateShader(type);

    std::string shaderString = loadShader(shaderFilename);
    const GLchar* shaderSource = shaderString.c_str();

    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);
    // shader: check whether compilation was successfully or not
    checkCompileErrors(shader, COMPILATION);

    return shader;
}

void Shader::checkCompileErrors(GLuint shader, bool type)
{
    GLint success;
    GLchar infolog[512];

    if(!type)
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(shader, 512, NULL, infolog);
            std::cerr
            << "ERROR::SHADER::COMPILATION_FAILED\n"
            << infolog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shader, 512, NULL, infolog);
            std::cerr
            << "ERROR::PROGRAM::SHADER::LINKING_FAILED\n"
            << infolog
            << "\n -- --------------------------------------------------- -- "
            << std::endl;
        }
    }
}

std::string Shader::loadShader(const std::string& shaderFilename)
{
    std::string code;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    try
    {
        // open file
        shaderFile.open("Shaders/" + shaderFilename);
        std::stringstream shaderStream;
        // read file
        shaderStream << shaderFile.rdbuf();
        // close file
        shaderFile.close();
        // convert stream into string
        code = shaderStream.str();
    }
    catch(std::ifstream::failure e)
    {
        std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }

    return code;
}
