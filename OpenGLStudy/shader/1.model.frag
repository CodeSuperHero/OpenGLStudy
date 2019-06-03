#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;

// uniform sampler2D texture_diffuse1;

struct Material
{
    sampler2D texture_diffuse1;
    sampler2D texture_specular1;
    float shininess;
};

struct Light
{
    vec3 position;
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float cutOff;
    float outerCutOff;
    float constant;
    float linear;
    float quadratic;
};

uniform vec3 viewPos;
uniform Material material;
uniform Light light;

void main()
{
    float distance = length(light.position - FragPos);
    //float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
    vec3 diffuseCol =  texture(material.texture_diffuse1, TexCoords).rgb;
    vec3 ambient = light.ambient * diffuseCol;// * attenuation;

    vec3 lightDir = normalize(light.position - FragPos);

    // float theta = dot(lightDir, normalize(-light.direction));
    // float epsilon = (light.cutOff - light.outerCutOff);
    // float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0f, 1.0f);

    // float temp = attenuation * intensity;

    vec3 norm = normalize(Normal);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = light.diffuse * diff * diffuseCol;// * temp;

    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * spec * texture(material.texture_specular1, TexCoords).rgb;// * temp;

    vec3 result = ambient + diffuse + specular;
    color = vec4(result, 1.0f);
}