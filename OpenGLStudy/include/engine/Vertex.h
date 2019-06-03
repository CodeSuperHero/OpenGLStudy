#pragma once
#include "engine/Engine.h"

namespace OSEngine
{
    struct Vertex
    {
    public:
        Vertex() {};
        ~Vertex() {};

        vec3 Position;
        vec3 Normal;
        vec2 TexCoords;
    private:

    };
}