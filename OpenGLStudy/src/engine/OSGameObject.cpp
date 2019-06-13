#include "engine/OSGameObject.h"
#include "engine/Context.h"

namespace OSEngine
{
    OSGameObject::~OSGameObject()
    {
        delete(mMeshRender);
        delete(mTransform);
    }
    void OSGameObject::Render(const Context & camera)
    {
        mMeshRender->Render(camera);
    }
}