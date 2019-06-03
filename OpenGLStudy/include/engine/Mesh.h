#pragma once
#include <vector>

#include "engine/Engine.h"

namespace OSEngine
{
    struct Vertex;
    struct TextureS;
    class Shader;

    class Mesh : OSObject
    {
    public:
        Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<TextureS> tex) : mVertices(ver), mIndices(ind), mTextures(tex)
        {
            SetupMesh();
        }

        ~Mesh() {};
        void Draw(Shader shader);
    private:
        std::vector<Vertex> mVertices;
        std::vector<unsigned int> mIndices;
        std::vector<TextureS> mTextures;
        unsigned int mVAO, mVBO, mEBO;
        void SetupMesh();
    };
}