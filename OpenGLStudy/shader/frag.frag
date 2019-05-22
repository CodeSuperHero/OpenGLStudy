#version 330 core

out vec4 FragColor;

in vec3 ourColor;
in vec2 texcoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
    FragColor = mix(texture(texture1, texcoord), texture(texture2, vec2(1 - texcoord.x, texcoord.y)), 0.5);
}