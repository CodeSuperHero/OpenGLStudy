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


#define SHARE_PTR_DEFINE(T)    \
class T;    \
using T##Ptr = std::shared_ptr<T>;    \
using T##WPtr = std::weak_ptr<T>;

#define UNIQUE_PTR_DEFINE(T)    \
class T;    \
using T##UPtr = std::unique_ptr<T>;    \

#define SELF_FACTORY(T) \
static T##Ptr New() { return std::make_shared<T>(); }

#define SELF_FACTORY_1(T, T1) \
static T##Ptr New(T1 t1) { return std::make_shared<T>(t1); }

#define SELF_FACTORY_2(T, T1, T2) \
static T##Ptr New(T1 t1, T2 t2) { return std::make_shared<T>(t1, t1); }
}