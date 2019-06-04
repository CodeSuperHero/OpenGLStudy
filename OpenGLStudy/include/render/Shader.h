#pragma once

#include <iostream>
#include "engine/Engine.h"

namespace OSEngine
{
    SHARE_PTR_DEFINE(Shader)

    class Shader final
    {
    public:
        SELF_FACTORY(Shader)

        Shader() {};
        Shader(const char* vertFileName, const char* fragFileName);
        ~Shader();
        Shader(const Shader& s) = delete;
        Shader& operator= (const Shader&) = delete;

        void Init(const char* vertFileName, const char* fragFileName);
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