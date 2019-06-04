#include <iostream>

#include "engine/Camera.h"
#include "engine/GInput.h"

void OSEngine::Camera::SetCamera()
{
    GInput::camera = this;
    mPosition = vec3(0.0f, 1.0f, 3.0f);
    mForward = vec3(0.0f, 0.0f, -1.0f);
    mUp = vec3(0.0f, 1.0f, 0.0f);
    mFov = 45.0f;
    mYaw = -45.0f;
    UpdateView();
    UpdateProjection();
}

void OSEngine::Camera::LookAt(vec3 position)
{

}

void OSEngine::Camera::Tick()
{
    float speed = 0.05f;
    if (GInput::GetKey(GLFW_KEY_W))
        mPosition += speed * mForward;
    if (GInput::GetKey(GLFW_KEY_S))
        mPosition -= speed * mForward;
    if (GInput::GetKey(GLFW_KEY_A))
        mPosition -= glm::normalize(glm::cross(mForward, mUp)) * speed;
    if (GInput::GetKey(GLFW_KEY_D))
        mPosition += glm::normalize(glm::cross(mForward, mUp)) * speed;

    if (firstMouse)
    {
        firstMouse = false;
        lastMousePosition = GInput::MousePosition();
    }

    vec2 offset = lastMousePosition - GInput::MousePosition();

    lastMousePosition = GInput::MousePosition();

    offset *= 0.05f;
    mYaw -= offset.x;
    mPitch += offset.y;

    if (mPitch > 89.0f)
        mPitch = 89.0f;
    if (mPitch < -89.0f)
        mPitch = -89.0f;

    vec3 forw;
    forw.x = cos(glm::radians(mPitch)) * cos(glm::radians(mYaw));
    forw.y = sin(glm::radians(mPitch));
    forw.z = cos(glm::radians(mPitch)) * sin(glm::radians(mYaw));
    mForward = glm::normalize(forw);
    UpdateView();
}

void OSEngine::Camera::ScrollBack(vec2 v)
{
    if (mFov >= 1.0f && mFov <= 45.0f)
        mFov -= v.y;
    if (mFov <= 1.0f)
        mFov = 1.0f;
    if (mFov >= 45.0f)
        mFov = 45.0f;

    UpdateProjection();
}

