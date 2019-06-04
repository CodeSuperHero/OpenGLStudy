#pragma once
#include <vector>
#include "engine/Engine.h"

namespace OSEngine
{
    SHARE_PTR_DEFINE(Shader)

    struct Vertex;
    struct TextureS;

    class Mesh : OSObject
    {
    public:
        Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<TextureS> tex) : mVertices(ver), mIndices(ind), mTextures(tex)
        {
            SetupMesh();
        }

        ~Mesh() {};
        void Draw(const ShaderPtr shader);
    private:
        std::vector<Vertex> mVertices;
        std::vector<unsigned int> mIndices;
        std::vector<TextureS> mTextures;
        unsigned int mVAO, mVBO, mEBO;
        void SetupMesh();
    };
}