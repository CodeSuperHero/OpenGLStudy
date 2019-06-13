#include "Scene.h"
#include "engine/Camera.h"
#include "engine/OSObject.h"
#include "engine/Context.h"

namespace OSEngine
{
    void Scene::Render()
    {
        Context context;
        context.lights = lights;

        for (size_t i = 0; i < cameras.size(); i++)
        {
            context.camer = cameras[i];

        }

        auto iter = objects.begin();
        while (iter != objects.end())
        {
            if (!context.camer->Render(iter->first))
                continue;
            auto objs = iter->second;
            for (size_t i = 0; i < objs.size(); i++)
            {
                objs[i]->Render(context);
            }
        }
    }
}