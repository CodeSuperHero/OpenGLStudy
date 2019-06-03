#include "engine/Light.h"
#include "render/Shader.h"
#include "render/Shader.h"
#include "engine/Camera.h"

namespace OSEngine
{
    void Light::Init(unsigned int * vbo)
    {
        glGenVertexArrays(1, &lightVao);
        glBindVertexArray(lightVao);
        glBindBuffer(GL_ARRAY_BUFFER, *vbo);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        shader = new Shader("lamp.vert", "lamp.frag");
        shader->SetVec3("lightPos", position);
    }

    void Light::Render(Camera* camera)
    {
        shader->Use();

        shader->SetMat44("view", camera->GetView());
        shader->SetMat44("projection", camera->GetProjection());
        mat4 model = mat4(1.0f);
        model = glm::translate(model, position);
        model = glm::scale(model, vec3(0.2f));
        shader->SetMat44("model", model);

        glBindVertexArray(lightVao);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
    }
}