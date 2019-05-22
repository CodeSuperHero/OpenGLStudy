#include "engine/ResourceObject.h"

namespace OSEngine
{
    ResourceObject::ResourceObject(const char * name, OSObject* obj)
    {
        mObjPath = name;
        mObject = obj;
        ++mRefCount;
    }

    ResourceObject::~ResourceObject()
    {
        delete mObject;
    }

    OSObject * ResourceObject::Load()
    {
        ++mRefCount;
        return mObject;
    }

    bool ResourceObject::UnLoad()
    {
        --mRefCount;
        return mRefCount == 0;
    }
}