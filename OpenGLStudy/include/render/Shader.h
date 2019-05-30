#pragma once

#include <iostream>
#include "engine/Engine.h"

namespace OSEngine
{
    class Shader final
    {
    public:
        Shader(const char* vertFileName, const char* fragFileName);
        ~Shader();

        int Id();
        void Use();
        void SetVec3(const std::string & name, vec3 value) const;
        void SetMat44(const std::string & name, mat4 value) const;
        void SetBool(const std::string &name, bool value) const;
        void SetInt(const std::string &name, int value) const;
        void SetFloat(const std::string &name, float value) const;

    private:
        void CompileShader(const char * vertCode, const char * fragCode);

    private:
        int mId;
    };
}