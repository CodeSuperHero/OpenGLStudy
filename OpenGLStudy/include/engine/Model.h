#pragma once
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "engine/Engine.h"
#include "engine/Mesh.h"
#include "engine/Vertex.h"
#include "engine/Texture.h"

namespace OSEngine
{
    class Model
    {
    public:
        Model() {}
        Model(const char *path)
        {
            LoadModel(path);
        }
        ~Model() {};

        void Draw(Shader shader);
        void LoadModel(const std::string path);
    private:
        void ProcessNode(aiNode *node, const aiScene *scene);
        Mesh ProcessMesh(aiMesh *mesh, const aiScene *scene);
        std::vector<TextureS> LoadMaterialTexture(aiMaterial *mat, aiTextureType type, std::string typeName);

        //--------------
        std::vector<Mesh> mMeshs;
        std::string mDirectory;
    };
}