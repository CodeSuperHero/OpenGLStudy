#pragma once

#include "engine/OSObject.h"
#include "engine/MeshRender.h"

namespace OSEngine
{
    class OSGameObject : public OSObject
    {
    public:
        virtual ~OSGameObject();

        void Render(const Context& camera) override;
    private:
        MeshRender* mMeshRender;
        Transform* mTransform;
    };
}