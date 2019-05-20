#include "engine/Resources.h"

#include "util/FileUtil.h"
#include "engine/Texture2D.h"

namespace OSEngine
{
    using namespace std;

    const string Resources::ROOT_PATH = "G:/Project/OpenGLStudy/OpenGLStudy";
    const string Resources::SHADER_PATH = ROOT_PATH +"/shader/";
    const string Resources::ASSET_PATH = ROOT_PATH + "/assets/";

    const char* Resources::LoadShader(const string shaderName)
    {
        auto fp = SHADER_PATH + shaderName;
        return FileUtil::Read(fp.c_str());
    }

    Texture2D Resources::LoadTexture(const string imageName)
    {
        auto tp = ASSET_PATH + imageName;
        Texture2D tex2D(imageName, tp);
        return tex2D;
    }
}