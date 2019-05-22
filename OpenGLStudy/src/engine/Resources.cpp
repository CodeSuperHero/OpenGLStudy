#include "engine/Resources.h"

#include "util/FileUtil.h"
#include "engine/Texture2D.h"

namespace OSEngine
{
    using namespace std;

    const string Resources::ROOT_PATH = "G:/Project/OpenGLStudy/OpenGLStudy";
    const string Resources::SHADER_PATH = ROOT_PATH +"/shader/";
    const string Resources::ASSET_PATH = ROOT_PATH + "/assets/";
    std::map<std::string, ResourceObject*> Resources::mResMap;

    const char* Resources::LoadShader(const string shaderName)
    {
        auto fp = SHADER_PATH + shaderName;
        return FileUtil::Read(fp.c_str());
    }

    Texture2D* Resources::LoadTexture(const string imageName, const int format, const bool turn)
    {
        auto tp = ASSET_PATH + imageName;
        auto it = mResMap.find(imageName);
        Texture2D* tex2D;
        if (it == mResMap.end())
        {
            tex2D = new Texture2D(imageName, tp, format, turn);
            auto res = new ResourceObject(imageName.c_str(), (OSObject*)tex2D);
            mResMap.insert(std::make_pair(imageName, res));
        }
        else
        {
            tex2D = dynamic_cast<Texture2D*>(it->second->Load());
        }
        return tex2D;
    }

    void Resources::UnLoad(std::string name)
    {
        auto it = mResMap.find(name);
        if (it == mResMap.end())
            return;

        if (it->second->UnLoad())
        {
            mResMap.erase(name);
            delete it->second;
        }
    }

    void Resources::UnLoad(OSObject * obj)
    {
        UnLoad(obj->Name());
    }
}