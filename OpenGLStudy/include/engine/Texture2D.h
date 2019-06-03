#pragma once

#include "engine/Engine.h"
#include "engine/Texture.h"
#include "engine/Resources.h"

namespace OSEngine
{
    class Texture2D final : public OSObject
    {
    public:
        Texture2D(std::string name, std::string path);
        virtual ~Texture2D();

        inline void Active(int unit)
        {
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, mId);
        }

        inline int Width() { return mWidth; }
        inline int Height() { return mHeight; }
        inline int Channel() { return mChannel; }
        inline int Format() { return mFormat; }
        inline unsigned int Id() { return mId; }
    public:

    private:
        int mWidth;
        int mHeight;
        int mChannel;
        int mFormat;
        unsigned int mId;
    };
}