#pragma once
#include <iostream>

namespace OSEngine
{
    class OSObject
    {
    public:
        OSObject() { }
        virtual ~OSObject() { }
        std::string Name() { return mName; }
    protected:
        std::string mName;
    };
}