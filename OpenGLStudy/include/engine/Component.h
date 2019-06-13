#pragma once
#include "engine/OSObject.h"

namespace OSEngine
{
    class Component : OSObject
    {
    public:
        Component() {}
        virtual ~Component() {  }
        virtual void Render(const Context& camera) override {}
    protected:

    };
}