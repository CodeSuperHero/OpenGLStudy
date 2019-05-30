#version 330 core

in vec3 Normal;
in vec3 FragPos;

out vec4 outColor;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;

void main()
{
    // float ambientStr = 0.2f;
    // vec3 ambient = ambientStr * lightColor;

    // vec3 norm = normalize(Normal);
    // vec3 lightDir = normalize(lightPos - FragPos);
    // float diff = max(dot(norm, lightDir), 0.0);
    // vec3 diffuse = diff * lightColor;

    // vec3 result = (ambient + diffuse) * objectColor;
    outColor = vec4(1.0f);
}