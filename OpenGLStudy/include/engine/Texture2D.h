#pragma once
#include <iostream>

#include "OSObject.h"
#include "glad/glad.h"

namespace OSEngine
{
    class Texture2D final : OSObject
    {
    public:
        Texture2D();
        Texture2D(std::string name, std::string path);
        ~Texture2D();

        inline void Active() { glBindTexture(GL_TEXTURE_2D, mId); }
        inline int Id() { return mId; }
        inline int Width() { return mWidth; }
        inline int Height() { return mHeight; }
        inline int Channel() { return mChannel; }
        inline std::string Name() { return mName; }
    private:
        unsigned int mId;
        int mWidth;
        int mHeight;
        int mChannel;
        std::string mName;
    };
}