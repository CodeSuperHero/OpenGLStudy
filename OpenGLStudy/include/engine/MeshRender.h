#pragma once
#include "render/Shader.h"
#include "engine/Texture2D.h"
#include "engine/Component.h"
#include "engine/Transform.h"
#include "engine/Camera.h"
#include "engine/Light.h"
#include "engine/Model.h"

namespace OSEngine
{
    SHARE_PTR_DEFINE(Shader)

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
        unsigned int vaoHandler;
        unsigned int vbo;

        ShaderPtr shader;
        ShaderPtr stencilShader;
        Texture2D* tex1;
        Texture2D* tex2;
        Camera camera;
        Model model;
        Light light;
    };
}