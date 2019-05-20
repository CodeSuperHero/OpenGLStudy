#include "render/Shader.h"
#include "engine/Resources.h"

#include "glad/glad.h"
namespace OSEngine
{
    Shader::Shader(const char* vertFileName, const char* fragFileName)
    {
        auto vertCode = OSEngine::Resources::LoadShader(vertFileName);
        auto fragCode = OSEngine::Resources::LoadShader(fragFileName);
        CompileShader(vertCode, fragCode);
    }

    Shader::~Shader()
    {
        glDeleteProgram(mId);
    }

    int Shader::Id()
    {
        return mId;
    }

    void Shader::Active()
    {
        glUseProgram(mId);
    }

    void Shader::setBool(const std::string & name, bool value) const
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string & name, int value) const
    {
        glUniform1i(glGetUniformLocation(mId, name.c_str()), value);
    }

    void Shader::setFloat(const std::string & name, float value) const
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