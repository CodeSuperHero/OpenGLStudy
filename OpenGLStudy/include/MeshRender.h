#pragma once
#include "render/Shader.h"
#include "engine/Texture2D.h"

namespace OSEngine
{
    class MeshRender final
    {
    public:
        MeshRender();
        ~MeshRender();
        void Init();
        void Render();
    private:
        void InitShader();
        void InitVAO();

    private:
        unsigned int shaderProgram;
        unsigned int vaoHandler;
        Shader* shader;
        OSEngine::Texture2D* tex1;
        OSEngine::Texture2D* tex2;
    };
}