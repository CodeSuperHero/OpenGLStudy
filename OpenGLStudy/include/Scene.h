#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "engine/Engine.h"

namespace OSEngine
{
    SHARE_PTR_DEFINE(OSObject)
    SHARE_PTR_DEFINE(Light)
    SHARE_PTR_DEFINE(Camera)

    class Context;
    class Scene
    {
    public:
        std::vector<LightPtr> lights;
        std::vector<CameraPtr> cameras;
        std::map<uint32_t, std::vector<OSObjectPtr>> objects;
        void Render();
    };
}