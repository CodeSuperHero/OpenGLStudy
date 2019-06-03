#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>

#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "engine/OSObject.h"

namespace OSEngine
{
    typedef glm::vec2 vec2;
    typedef glm::vec3 vec3;
    typedef glm::vec4 vec4;
    typedef glm::quat quat;
    typedef glm::mat4 mat4;

    inline quat normalize(const quat& q)
    {
        float_t sqrLen = glm::dot(q, q);
        if (sqrLen <= 0) // Problem
            return quat(1, 0, 0, 0);
        float_t oneOverLen = 1 / glm::sqrt(sqrLen);
        return quat(q.w * oneOverLen, q.x * oneOverLen, q.y * oneOverLen, q.z * oneOverLen);
    }
}