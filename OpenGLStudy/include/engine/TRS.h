#pragma once

#include "engine/Engine.h"

namespace OSEngine
{
    class TRS
    {
    public:
        TRS() {}
        ~TRS() {}
        mat4 Model()
        {
            mat4 m = glm::toMat4(r);
            m = glm::scale(m, s);
            m[3][0] = t.x;
            m[3][1] = t.y;
            m[3][2] = t.z;
            return m;
        }

        vec3 t;
        quat r;
        vec3 s;
    private:

    };
}