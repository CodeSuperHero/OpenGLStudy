#include "game.h"

#include <iostream>
#include <string>

#include "engine/Resources.h"

Game::Game(GLFWwindow* win)
{
    window = win;
    gInput = new GInput();
    render = new OSEngine::MeshRender();
}

Game::~Game()
{
    delete(gInput);
    delete(render);
}

void Game::Init()
{
    std::cout << "[Game Init] BEGIN" << std::endl;
    render->Init();
    std::cout << "[Game Init] End" << std::endl;
}

void Game::Tick()
{
    gInput->ProcessInput(window);

}

void Game::Draw()
{
    render->Render();
}

void Game::UnInit()
{
    std::cout << "[Game UnInit]" << std::endl;
}

