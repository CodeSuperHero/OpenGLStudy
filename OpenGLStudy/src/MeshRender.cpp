#include "engine/MeshRender.h"

#include "engine/Resources.h"
#include "engine/OSObject.h"

#include "Game.h"

namespace OSEngine
{
    MeshRender::MeshRender()
    {
        model.LoadModel("nanosuit/nanosuit.obj");
        tex1 = Resources::LoadTexture("container2.png");
        tex2 = Resources::LoadTexture("container2_specular.png");
    }

    MeshRender::~MeshRender()
    {
        Resources::UnLoad(tex1);
        Resources::UnLoad(tex2);
    }

    void MeshRender::InitShader()
    {
        shader = Shader::New();
        shader->Init("1.model.vert", "1.model.frag");
        stencilShader = Shader::New();
        stencilShader->Init("1.stencil.vert", "1.stencil.frag");
    }

    void MeshRender::Init()
    {
        camera.SetCamera();
        InitShader();
        InitVAO();
        light.Init(&vbo);
    }

    vec3 cubePositions[] =
    {
       vec3(0.0f,  0.0f,  0.0f),
       vec3(2.0f,  5.0f, -15.0f),
       vec3(2.0f,  1.0f,  0.0f),
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
        camera.Tick();
        vec3 diffuseColor = vec3(0.8f, 0.8f, 0.8f);
        vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);

        shader->Use();
        shader->SetVec3("light.position", camera.Position());
        shader->SetVec3("light.direction", camera.Forward());
        shader->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        shader->SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));

        shader->SetVec3("light.ambient", ambientColor);
        shader->SetVec3("light.diffuse", diffuseColor);
        shader->SetVec3("light.specular", vec3(1.0f, 1.0f, 1.0f));
        shader->SetFloat("light.constant", 1.0f);
        shader->SetFloat("light.linear", 0.09f);
        shader->SetFloat("light.quadratic", 0.032);

        shader->SetFloat("material.shininess", 64.0f);

        shader->SetVec3("viewPos", camera.Position());

        shader->SetMat44("view", camera.GetView());
        shader->SetMat44("projection", camera.GetProjection());

        glStencilFunc(GL_ALWAYS, 1, 0xFF);
        glStencilMask(0xFF);

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(1.0f, 0.0f, -1.0f));   // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	        // it's a bit too big for our scene, so scale it down
        shader->SetMat44("model", model);
        this->model.Draw(shader);
        //glBindVertexArray(vaoHandler);
        //for (size_t i = 0; i < 9; i++)
        //{
        //    model = mat4(1.0f);
        //    model = glm::translate(model, cubePositions[i]);
        //    float_t angle = 20.0f * i;
        //    model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            //shader.SetMat44("model", model);
            //glDrawArrays(GL_TRIANGLES, 0, 36);
        //}
       // glBindVertexArray(0);

        //light.Render(&camera);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        stencilShader->Use();
        stencilShader->SetMat44("view", camera.GetView());
        stencilShader->SetMat44("projection", camera.GetProjection());
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(3.0f, 0.0f, -1.0f));
        model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
        stencilShader->SetMat44("model", model);
        //glBindVertexArray(vaoHandler);
        //glDrawArrays(GL_TRIANGLES, 0, 36);
        //glBindVertexArray(0);
        this->model.Draw(stencilShader);
        glStencilMask(0xFF);
        glEnable(GL_DEPTH_TEST);
    }

    float vertices[] =
    {
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
         0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
        -0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
         0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
         0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
         0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
         0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
    };

    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };

    void MeshRender::InitVAO()
    {
        glGenVertexArrays(1, &vaoHandler);
        glGenBuffers(1, &vbo);

        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(vaoHandler);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));

        glBindVertexArray(0);
    }
}