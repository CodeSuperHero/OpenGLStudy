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

        static Texture2D* LoadTexture(const std::string ImageName);

        static void UnLoad(std::string name);
        static void UnLoad(OSObject* obj);

        static inline std::string GetAssetPath(std::string name)
        {
            return ASSET_PATH + name;
        }
    private:
        static const std::string ROOT_PATH;
        static const std::string SHADER_PATH;
        static const std::string ASSET_PATH;
        static const int ASSET_PATH_LENGTH;
        static std::map<std::string, ResourceObject*> mResMap;
    };
}