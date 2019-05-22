#pragma once
#include <iostream>
#include "engine/OSObject.h"

namespace OSEngine
{
    class ResourceObject final
    {
    public:
        ResourceObject(const char* name, OSObject* obj);
        ~ResourceObject();

        OSObject* Load();
        bool UnLoad();

        inline const char* Name() { return mObjPath; }
        inline size_t RefCount() { return mRefCount; }
    private:
        const char* mObjPath;
        size_t mRefCount;
        OSObject* mObject;
    };
}