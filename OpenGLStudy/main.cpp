#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Game.h"

#include "engine/Engine.h"
#include "render/Shader.h"
#include "engine/Camera.h"
#include "engine/Texture2D.h"
#include "engine/Model.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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

// settings
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    GLFWwindow* window = glfwCreateWindow(Game::SCR_WIDTH, Game::SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    glViewport(0, 0, Game::SCR_WIDTH, Game::SCR_HEIGHT);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    Game g(window);// = new Game(window);
    g.Init();
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_STENCIL_TEST);
    glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

    unsigned int vaoHandler;
    unsigned int vbo;

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

    OSEngine::vec3 diffuseColor(0.8f, 0.8f, 0.8f);
    OSEngine::vec3 ambientColor(0.1f, 0.1f, 0.1f);

    auto shader = OSEngine::Shader::New();
    shader->Init("1.model.vert", "1.model.frag");
    auto stencilShader = OSEngine::Shader::New();
    stencilShader->Init("1.stencil.vert", "1.stencil.frag");
    OSEngine::Camera camera;
    OSEngine::Model model;
    camera.SetCamera();
    model.LoadModel("nanosuit/nanosuit.obj");

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
        g.Tick();
        //g.Draw();
        camera.Tick();

        glStencilFunc(GL_ALWAYS, 0x01, 0xFF);
        glStencilMask(0xFF);

        shader->Use();
        shader->SetVec3("light.position", camera.Position());
        shader->SetVec3("light.direction", camera.Forward());
        shader->SetFloat("light.cutOff", glm::cos(glm::radians(12.5f)));
        shader->SetFloat("light.outerCutOff", glm::cos(glm::radians(17.5f)));
        shader->SetVec3("light.ambient", ambientColor);
        shader->SetVec3("light.diffuse", diffuseColor);
        shader->SetVec3("light.specular", OSEngine::vec3(1.0f, 1.0f, 1.0f));
        shader->SetFloat("light.constant", 1.0f);
        shader->SetFloat("light.linear", 0.09f);
        shader->SetFloat("light.quadratic", 0.032);
        shader->SetFloat("material.shininess", 64.0f);
        shader->SetVec3("viewPos", camera.Position());
        shader->SetMat44("view", camera.GetView());
        shader->SetMat44("projection", camera.GetProjection());
        OSEngine::mat4 modelMat(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -1.0f));   // translate it down so it's at the center of the scene
        modelMat = glm::scale(modelMat, glm::vec3(0.2f, 0.2f, 0.2f));	        // it's a bit too big for our scene, so scale it down
        shader->SetMat44("model", modelMat);
        model.Draw(shader);

        glStencilFunc(GL_NOTEQUAL, 0x01, 0xFF);
        glStencilMask(0x00);
        glDisable(GL_DEPTH_TEST);

        stencilShader->Use();
        stencilShader->SetMat44("view", camera.GetView());
        stencilShader->SetMat44("projection", camera.GetProjection());
        modelMat = glm::mat4(1.0f);
        modelMat = glm::translate(modelMat, glm::vec3(0.0f, 0.0f, -1.0f));
        modelMat = glm::scale(modelMat, glm::vec3(0.21f, 0.2f, 0.21f));
        stencilShader->SetMat44("model", modelMat);
        model.Draw(stencilShader);

        glEnable(GL_DEPTH_TEST);
        glStencilMask(0xFF);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    //g.UnInit();
    glfwTerminate();
    return 0;
}

void Draw(OSEngine::Shader shader, unsigned int vao)
{
    //for (auto i = 0; i < mMeshs.size(); i++)
        //mMeshs[0].Draw(shader, vao);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mEBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices[0], GL_STATIC_DRAW);
    //glDrawElements(GL_TRIANGLES, mIndices.size(), GL_UNSIGNED_INT, 0);
    shader.Use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glBindVertexArray(0);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    std::cout << "framebuffer_size_callback" << std::endl;
    glViewport(0, 0, width, height);
}