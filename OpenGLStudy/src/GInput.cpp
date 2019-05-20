#include "GInput.h"

void GInput::ProcessInput(GLFWwindow* win)
{
    if (glfwGetKey(win, GLFW_KEY_ESCAPE))
    {
        glfwSetWindowShouldClose(win, true);
    }
}