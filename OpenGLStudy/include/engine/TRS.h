#pragma once

#include "engine/Engine.h"

namespace OSEngine
{
    class TRS
    {
    public:
        TRS() {}
        ~TRS() {}

        vec3 t;
        quat r;
        vec3 s;
    private:

    };
}