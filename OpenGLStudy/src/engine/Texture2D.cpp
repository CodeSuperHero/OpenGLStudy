#include "engine/Texture2D.h"

#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/common.hpp>

namespace OSEngine
{
    Texture2D::Texture2D(std::string name, std::string path)
    {
        auto img = stbi_load(path.c_str(), &mWidth, &mHeight, &mChannel, 0);
        if (img)
        {
            glGenTextures(1, &mId);

            mName = name;

            if (mChannel == 1)
                mFormat = GL_RED;
            else if (mChannel == 2)
                mFormat = GL_RGB;
            else if (mChannel == 4)
                mFormat = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, mId);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, img);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glBindTexture(GL_TEXTURE_2D, 0);
        }
        else
        {
            std::cout << "Failed to load texture" << std::endl;
        }
        stbi_image_free(img);
    }

    Texture2D::~Texture2D()
    {
        glDeleteTextures(1, &mId);
    }
}