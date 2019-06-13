#pragma once
#include <set>
#include "engine/Engine.h"

namespace OSEngine
{
    class Camera final
    {
    public:
        Camera() : firstMouse(true) {  }
        ~Camera() {}

        void SetCamera();
        void LookAt(vec3 position);
        mat4 GetView() { return mView; }
        mat4 GetProjection() { return mProjection; }

        void Position(vec3 value) { mPosition = value; UpdateView(); }
        vec3 Position() { return mPosition; }

        void Forward(vec3 value) { mForward = value; UpdateView(); }
        vec3 Forward() { return mForward; }

        void Up(vec3 value) { mUp = value; UpdateView(); }
        vec3 Up() { return mUp; }

        void Tick();
        void ScrollBack(vec2 v);

        bool Render(uint32_t layer) { return mLayers.count(layer); }

        const std::set<uint32_t> Layers() { return mLayers; }

    private:
        void UpdateView()
        {
            mView = glm::lookAt(mPosition, mPosition + mForward, mUp);
        }

        void UpdateProjection()
        {
            mProjection = glm::perspective(glm::radians(mFov), 800.0f / 600.0f, 0.1f, 100.0f);
        }

        bool firstMouse;
        float_t mPitch, mYaw;
        float_t mFov;
        vec2 lastMousePosition;
        vec3 mPosition;
        vec3 mForward;
        vec3 mUp;
        mat4 mView;
        mat4 mProjection;

        std::set<uint32_t> mLayers;
    };
}