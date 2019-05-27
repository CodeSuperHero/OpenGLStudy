#pragma once
#include "render/Shader.h"
#include "engine/Texture2D.h"
#include "engine/Component.h"
#include "engine/Transform.h"
#include "engine/Camera.h"

namespace OSEngine
{
    class MeshRender final : Component
    {
    public:
        MeshRender();
        ~MeshRender();
        void Init();
        void Render();
    private:
        void InitShader();
        void InitVAO();
    public:
        Transform transform;
    private:
        unsigned int shaderProgram;
        unsigned int vaoHandler;
        Shader* shader;
        Texture2D* tex1;
        Texture2D* tex2;
        Camera camera;
    };
}