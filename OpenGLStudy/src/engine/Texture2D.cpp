#include "engine/Texture2D.h"

#include "stb_image.h"

namespace OSEngine
{
    Texture2D::Texture2D(std::string name, std::string path)
    {
        Texture2D();
        mName = name;
        auto img = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannel, 0);
        if (img)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, mWidth, mHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(img);
    }

    Texture2D::Texture2D()
    {
        glGenTextures(1, &mId);
        glBindTexture(GL_TEXTURE_2D, mId);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &mId);
    }
}