#include "render/Shader.h"

#include "engine/Resources.h"

namespace OSEngine
{
    Shader::Shader(const char* vertFileName, const char* fragFileName)
    {
        Init(vertFileName, fragFileName);
    }

    Shader::~Shader()
    {
        glDeleteProgram(mId);
    }

    void Shader::Init(const char * vertFileName, const char * fragFileName)
    {
        std::cout << " SHADER INIT. Vert Shader :" << vertFileName << ", Frag Shader :" << fragFileName << std::endl;
        auto vertCode = OSEngine::Resources::LoadShader(vertFileName);
        auto fragCode = OSEngine::Resources::LoadShader(fragFileName);
        CompileShader(vertCode, fragCode);
    }

    int Shader::Id()
    {
        return mId;
    }

    void Shader::Use()
    {
        glUseProgram(mId);
    }

    void Shader::SetVec3(const std::string & name, vec3 value) const
    {
        glUniform3f(glGetUniformLocation(mId, name.c_str()), value.x, value.y, value.z);
    }

    void Shader::SetMat44(const std::string & name, mat4 value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(mId, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
    }

    void Shader::SetBool(const std::string & name, bool value) const
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
    }

    void Shader::SetInt(const std::string & name, int value) const
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
    }

    void Shader::SetFloat(const std::string & name, float value) const
    {
        glUniform1f(glGetUniformLocation(mId, name.c_str()), value);
    }

    void Shader::CompileShader(const char * vertCode, const char * fragCode)
    {

        unsigned int vertex, fragment;
        int success;
        char infoLog[512];

        vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &vertCode, NULL);
        glCompileShader(vertex);
        glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return;
        };

        fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &fragCode, NULL);
        glCompileShader(fragment);
        glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(fragment, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
            return;
        };

        mId = glCreateProgram();
        glAttachShader(mId, vertex);
        glAttachShader(mId, fragment);
        glLinkProgram(mId);
        glGetProgramiv(mId, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(mId, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
            return;
        }
        glDeleteShader(vertex);
        glDeleteShader(fragment);
    }
}