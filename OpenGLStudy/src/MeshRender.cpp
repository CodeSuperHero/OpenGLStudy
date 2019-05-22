#include "MeshRender.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "engine/Resources.h"

namespace OSEngine
{
    MeshRender::MeshRender()
    {
        tex1 = Resources::LoadTexture("container.jpg", GL_RGB, false);
        tex2 = Resources::LoadTexture("awesomeface.png", GL_RGBA, true);
    }

    MeshRender::~MeshRender()
    {

    }

    void MeshRender::Init()
    {
        InitShader();
        InitVAO();

        tex1->Active(GL_TEXTURE0);
        tex2->Active(GL_TEXTURE1);

        shader->Use();
        shader->setInt("texture1", 0);
        shader->setInt("texture2", 1);
    }

    void MeshRender::Render()
    {
        glBindVertexArray(vaoHandler);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    void MeshRender::InitShader()
    {
        shader = new Shader("vertex.vert", "frag.frag");
    }

    void MeshRender::InitVAO()
    {
        float vertices[] = {
            //     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
            0.5f,  0.5f,  0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // 右上
            0.5f,  -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // 右下
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // 左下
            -0.5f, 0.5f,  0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // 左上
        };

        unsigned int indices[] = { 0, 1, 3,  1, 2, 3 };

        glGenVertexArrays(1, &vaoHandler);


        unsigned int VBO;
        glGenBuffers(1, &VBO);

        unsigned int EBO;
        glGenBuffers(1, &EBO);

        glBindVertexArray(vaoHandler);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}