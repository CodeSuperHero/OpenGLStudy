#version 330 core

in vec2 TexCoords;

out vec4 color;

// struct Material1
// {
//     sampler2D texture_diffuse1;
//     sampler2D texture_specular1;
// };

// uniform Material1 material;

void main()
{
    color = vec4(0.04, 0.28, 0.26, 1.0);
}