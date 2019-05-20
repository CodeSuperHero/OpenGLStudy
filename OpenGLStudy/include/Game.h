#pragma once

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "GInput.h"
#include "MeshRender.h"

class Game final
{
public:
    Game(GLFWwindow* win);
    ~Game();

    void Init();
    void Tick();
    void Draw();
    void UnInit();

private:
    GLFWwindow* window;
    GInput* gInput;
    OSEngine::MeshRender* render;
};

