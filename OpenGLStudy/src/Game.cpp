#include "game.h"

#include <iostream>
#include <string>

#include "engine/Resources.h"
#include "engine/Transform.h"
#include "engine/GInput.h"

Game::Game(GLFWwindow* win)
{
    window = win;
    render = new OSEngine::MeshRender();
}

Game::~Game()
{
    delete(render);
}

void Game::Init()
{
    OSEngine::Transform transform;
    transform.LocalPosition(OSEngine::vec3(1.0f, 1.0f, 0.0f));

    OSEngine::GInput::Init(window);

    std::cout << "[Game Init] BEGIN" << std::endl;
    render->Init();

    OSEngine::Component* trans = (OSEngine::Component*)new OSEngine::Transform();
    delete trans;
    std::cout << "[Game Init] End" << std::endl;
}

void Game::Tick()
{
    OSEngine::GInput::Tick();
}

void Game::Draw()
{
    render->Render();
}

void Game::UnInit()
{
    std::cout << "[Game UnInit]" << std::endl;
}

