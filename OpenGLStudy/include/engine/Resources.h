#pragma once
#include <iostream>
#include <map>

//#include "engine/Texture2D.h"
#include "engine/ResourceObject.h"

namespace OSEngine
{
    class Texture2D;
    class Resources final
    {
    public:
        static const char* LoadShader(const std::string shaderName);

        static Texture2D* LoadTexture(const std::string ImageName, const int format, const bool turn);

        static void UnLoad(std::string name);
        static void UnLoad(OSObject* obj);
    private:
        static const std::string ROOT_PATH;
        static const std::string SHADER_PATH;
        static const std::string ASSET_PATH;
        static std::map<std::string, ResourceObject*> mResMap;
    };
}