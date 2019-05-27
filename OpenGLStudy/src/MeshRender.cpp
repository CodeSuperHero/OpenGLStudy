#include "engine/MeshRender.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "engine/Resources.h"
#include "engine/OSObject.h"

#include "Game.h"

namespace OSEngine
{
    MeshRender::MeshRender()
    {
        tex1 = Resources::LoadTexture("container.jpg", GL_RGB, false);
        tex2 = Resources::LoadTexture("awesomeface.png", GL_RGBA, true);
    }

    MeshRender::~MeshRender()
    {
        Resources::UnLoad(tex1);
        Resources::UnLoad(tex2);
    }

    void MeshRender::InitShader()
    {
        shader = new Shader("6.1.vertex.vert", "6.1.frag.frag");
    }

    void MeshRender::Init()
    {
        InitShader();
        InitVAO();
        camera.SetCamera();

        tex1->Active(GL_TEXTURE0);
        tex2->Active(GL_TEXTURE1);

        shader->Use();
        shader->SetInt("texture1", 0);
        shader->SetInt("texture2", 1);
    }

    vec3 cubePositions[] = {
       vec3(0.0f,  0.0f,  0.0f),
       vec3(2.0f,  5.0f, -15.0f),
       vec3(-1.5f, -2.2f, -2.5f),
       vec3(-3.8f, -2.0f, -12.3f),
       vec3(2.4f, -0.4f, -3.5f),
       vec3(-1.7f,  3.0f, -7.5f),
       vec3(1.3f, -2.0f, -2.5f),
       vec3(1.5f,  2.0f, -2.5f),
       vec3(1.5f,  0.2f, -1.5f),
       vec3(-1.3f,  1.0f, -1.5f)
    };

    void MeshRender::Render()
    {
        //mat4 view = mat4(1.0f);
        //view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        camera.Tick();
        //mat4 projection = mat4(1.0f);
        //projection = glm::perspective(glm::radians(45.0f), (float_t)Game::SCR_WIDTH / (float_t)Game::SCR_HEIGHT, 0.1f, 100.0f);
        //projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
        shader->Use();
        shader->SetMat44("view", camera.GetView());
        shader->SetMat44("projection", camera.GetProjection());

        glBindVertexArray(vaoHandler);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            mat4 model = mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float angle = 20.0f * i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
            shader->SetMat44("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    float vertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    void MeshRender::InitVAO()
    {
        glGenVertexArrays(1, &vaoHandler);

        unsigned int VBO, EBO;
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(vaoHandler);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        //glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
    }
}