#pragma once
#include <iostream>

#include "OSObject.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace OSEngine
{
    class Texture2D final : OSObject
    {
    public:
        Texture2D(std::string name, std::string path, int format, const bool turn);
        virtual ~Texture2D();

        inline void Active(int unit)
        {
            glActiveTexture(unit);
            glBindTexture(GL_TEXTURE_2D, mId);
        }

        inline int Id() { return mId; }
        inline int Width() { return mWidth; }
        inline int Height() { return mHeight; }
        inline int Channel() { return mChannel; }
    private:
        void Init();
    private:
        unsigned int mId;
        int mWidth;
        int mHeight;
        int mChannel;
    };
}