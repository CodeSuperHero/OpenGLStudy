#pragma once

#include <iostream>
namespace OSEngine
{
    class Shader final
    {
    public:
        Shader(const char* vertFileName, const char* fragFileName);
        ~Shader();

        int Id();
        void Active();
        void setBool(const std::string &name, bool value) const;
        void setInt(const std::string &name, int value) const;
        void setFloat(const std::string &name, float value) const;

    private:
        void CompileShader(const char * vertCode, const char * fragCode);

    private:
        int mId;
    };
}