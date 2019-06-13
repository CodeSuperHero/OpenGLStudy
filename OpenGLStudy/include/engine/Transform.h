#pragma once
#include "engine/Engine.h"
#include "engine/Component.h"
#include "engine/TRS.h"

namespace OSEngine
{
    class Transform final : Component
    {
    public:
        Transform() { }
        ~Transform() { }

        enum
        {
            EPositionChanged = 1 << 0,
            ERotationChanged = 1 << 1,
            EScaleChanged = 1 << 3,
            ETRSChanged = EPositionChanged | ERotationChanged | EScaleChanged,
        };

        void LocalPosition(const vec3& pos)
        {
            trs.t = pos;
            changeMask |= EPositionChanged;
        }

        vec3 LocalPosition() { return trs.t; }

        void LocalRotation(const quat& quat)
        {
            trs.r = normalize(quat);
            changeMask |= ERotationChanged;
        }

        quat LocalRotation() { return trs.r; }

        void LocalScale(const vec3& scale)
        {
            trs.s = scale;
            changeMask |= EScaleChanged;
        }

        vec3 LocalScale() { return trs.s; }

        void EulerAngles(const vec3& euler) { trs.r = quat(glm::radians(euler)); }

        vec3 EulerAngles() { return glm::eulerAngles(trs.r); }

        uint32_t ChangeMask()
        {
            uint32_t temp = 0;
            if (changeMask >0)
            {
                uint32_t temp = changeMask;
                changeMask = 0;
            }
        }

        mat4 Model() { return trs.Model(); }
    private:
        TRS trs;
        uint32_t changeMask;
        mat4 mModel;
    };
}

