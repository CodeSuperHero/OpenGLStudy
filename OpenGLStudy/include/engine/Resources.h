#pragma once
#include <iostream>
#include "engine/Texture2D.h"

namespace OSEngine
{
    class Resources final
    {
    public:
        static const char* LoadShader(const std::string shaderName);

        static Texture2D LoadTexture(const std::string ImageName);
    private:
        static const std::string ROOT_PATH;
        static const std::string SHADER_PATH;
        static const std::string ASSET_PATH;
    };
}