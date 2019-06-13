#pragma once
#include <iostream>

#include "engine/Engine.h"

namespace OSEngine
{
    class Context;
    SHARE_PTR_DEFINE(OSObject)
    class OSObject
    {
    public:
        SELF_FACTORY(OSObject)

        OSObject() { }
        virtual ~OSObject() { }
        std::string Name() { return mName; }
        uint32_t layer;
        virtual void Render(const Context& camera) = 0;
    protected:
        std::string mName;
    };
}