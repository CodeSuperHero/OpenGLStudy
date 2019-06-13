#pragma once
#include <vector>

namespace OSEngine
{
    class CameraPtr;
    class LightPtr;

    class Context
    {
    public:
        CameraPtr camer;
        std::vector<LightPtr> lights;
    };
}