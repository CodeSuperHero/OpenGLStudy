#include "engine/Model.h"
#include "engine/Texture2D.h"
#include "engine/Resources.h"
#include "render/Shader.h"

namespace OSEngine
{
    using namespace std;

    void Model::Draw(const ShaderPtr shader)
    {
        for (auto i = 0; i < mMeshs.size(); i++)
            mMeshs[i].Draw(shader);
    }

    void Model::LoadModel(const string path)
    {
        Assimp::Importer importer;
        auto scene = importer.ReadFile(Resources::GetAssetPath(path), aiProcess_Triangulate | aiProcess_FlipUVs);
        if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
        {
            cout << "ERROR::ASSIMP::" << importer.GetErrorString() << endl;
            return;
        }
        mDirectory = path.substr(0, path.find_last_of("/") + 1);
        ProcessNode(scene->mRootNode, scene);
    }

    void Model::ProcessNode(aiNode * node, const aiScene * scene)
    {
        cout << "ProcessNode mNumMeshes :" << node->mNumMeshes << "ProcessNode mNumChildren :" << node->mNumChildren << endl;
        for (unsigned int i = 0; i < node->mNumMeshes; i++)
        {
            aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
            mMeshs.push_back(ProcessMesh(mesh, scene));
        }

        for (unsigned int i = 0; i < node->mNumChildren; i++)
        {
            ProcessNode(node->mChildren[i], scene);
        }
    }

    Mesh Model::ProcessMesh(aiMesh * mesh, const aiScene * scene)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indices;
        vector<TextureS> textures;

        for (unsigned int i = 0; i < mesh->mNumVertices; i++)
        {
            Vertex vertex;
            aiVector3D temp = mesh->mVertices[i];
            vertex.Position.x = temp.x;
            vertex.Position.y = temp.y;
            vertex.Position.z = temp.z;

            temp = mesh->mNormals[i];
            vertex.Normal.x = temp.x;
            vertex.Normal.y = temp.y;
            vertex.Normal.z = temp.z;

            if (mesh->mTextureCoords[0])
            {
                temp = mesh->mTextureCoords[0][i];
                vertex.TexCoords.x = temp.x;
                vertex.TexCoords.y = temp.y;
            }
            else
            {
                vertex.TexCoords = vec2(0.0f, 0.0f);
            }
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < mesh->mNumFaces; i++)
        {
            aiFace face = mesh->mFaces[i];
            for (unsigned int j = 0; j < face.mNumIndices; j++)
            {
                indices.push_back(face.mIndices[j]);
            }
        }

        if (mesh->mMaterialIndex >= 0)
        {
            auto material = scene->mMaterials[mesh->mMaterialIndex];
            vector<TextureS> diffuseMaps = LoadMaterialTexture(material, aiTextureType_DIFFUSE, "texture_diffuse");
            if (diffuseMaps.size() > 0)
                textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());

            vector<TextureS> specularMaps = LoadMaterialTexture(material, aiTextureType_SPECULAR, "texture_specular");
            if (specularMaps.size() > 0)
                textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        }

        return Mesh(vertices, indices, textures);
    }

    std::vector<TextureS> Model::LoadMaterialTexture(aiMaterial * mat, aiTextureType type, std::string typeName)
    {
        vector<TextureS> textures;
        for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
        {
            aiString str;
            mat->GetTexture(type, i, &str);
            TextureS texture;
            string path = mDirectory + string(str.C_Str());
            texture.id = Resources::LoadTexture(path)->Id();
            texture.type = typeName;
            textures.push_back(texture);
        }
        return textures;
    }
}