#pragma once
#include <iostream>
#include "GLFW/glfw3.h"

#include "engine/Engine.h"
#include "engine/Camera.h"

namespace OSEngine
{
    class GInput final
    {
    public:
        static void Init(GLFWwindow* win)
        {
            window = win;
            glfwSetInputMode(win, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            glfwSetCursorPosCallback(window, InputMouseCallback);
            glfwSetScrollCallback(window, InputScrollCallback);
        }

        static void Tick()
        {
            if (glfwGetKey(window, GLFW_KEY_ESCAPE))
                glfwSetWindowShouldClose(window, true);
        }

        static bool GetKey(uint32_t key) { return glfwGetKey(window, key); }

        static bool GetMouseKey(uint32_t key) {   }

        static vec2 MousePosition() { return mousePosition; }
    private:
        static void InputMouseCallback(GLFWwindow* win, double xpos, double ypos)
        {
            mousePosition = vec2(xpos, ypos);
        }

        static void InputScrollCallback(GLFWwindow* win, double xoffset, double yoffset)
        {
            if (nullptr != camera)
                camera->ScrollBack(vec2(xoffset, yoffset));
        }
    public:
        static Camera* camera;

    private:
        static vec2 scroll;
        static vec2 mousePosition;
        static GLFWwindow* window;
    };
}