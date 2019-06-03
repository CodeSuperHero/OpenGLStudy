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
        shader = new Shader("1.model.vert", "1.model.frag");
    }

    void MeshRender::Init()
    {
        camera.SetCamera();
        InitShader();
        InitVAO();
        light.Init(&vbo);

        /*tex1->Active(GL_TEXTURE0);
        tex2->Active(GL_TEXTURE1);
        shader->Use();
        shader->SetInt("material.diffuse", 0);
        shader->SetInt("material.specular", 1);*/
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
        /*GLfloat currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;*/
        /*vec3 lightColor;
        lightColor.x = sin(glfwGetTime() * 2.0f);
        lightColor.y = sin(glfwGetTime() * 0.7f);
        lightColor.z = sin(glfwGetTime() * 1.3f);*/
        vec3 diffuseColor = vec3(0.8f, 0.8f, 0.8f);// lightColor * glm::vec3(0.5f);
        vec3 ambientColor = vec3(0.1f, 0.1f, 0.1f);

        shader->Use();
        //std::cout << "[ MeshRender::Render] shader use id :" << shader->Id() << std::endl;
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

        //shader->SetVec3("material.specular", vec3(0.5f, 0.5f, 0.5f));
        shader->SetFloat("material.shininess", 64.0f);

        shader->SetVec3("viewPos", camera.Position());

        shader->SetMat44("view", camera.GetView());
        shader->SetMat44("projection", camera.GetProjection());

        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        shader->SetMat44("model", model);
        //this->model.Draw(*shader);

        glBindVertexArray(vaoHandler);
        for (size_t i = 0; i < 9; i++)
        {
            model = mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            float_t angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            shader->SetMat44("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);

        light.Render(&camera);
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