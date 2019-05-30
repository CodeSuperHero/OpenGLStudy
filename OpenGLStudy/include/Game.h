#pragma once

#include "engine/MeshRender.h"

class Game final
{
public:
    Game(GLFWwindow* win);
    ~Game();

    void Init();
    void Tick();
    void Draw();
    void UnInit();

    const static unsigned int SCR_WIDTH = 800;
    const static unsigned int SCR_HEIGHT = 600;

private:
    GLFWwindow* window;
    OSEngine::MeshRender* render;
};

