#version 330 core
#define MAX_LIGHTS 1

out vec4 FragColor;

in vec3 position;
in vec2 uvs;
in vec3 normal;

struct Light {
    int type;
    float intensity;
    vec3 color;
    vec3 position;
    float linear;
    float constant;
    float quadratic;
    float innerCutoff;
    float outerCutoff;
};

struct Material {
    sampler2D diffuseMap;
    sampler2D specularMap;
    sampler2D normalMap;
    sampler2D shadowMap;
    vec3 diffuseColor;
    vec3 specularColor;
    vec3 ambientColor;
    float shininess;
    float shininess_strength;
    float normal_strength;
    int hasDiffuse;
    int hasSpecular;
    int hasNormal;
    vec2 diffuse_tiling;
    vec2 specular_tiling;
    vec2 normal_tiling;
};

uniform vec3 camPos;
uniform sampler2D textureMap;
uniform Light lights[MAX_LIGHTS];
uniform Material material;

vec3 CalcPointLight(Light light, vec3 norm, vec3 position, vec3 viewDir) {
    vec3 lightDir = normalize(light.position - position);
    float diff = max(dot(norm, lightDir), 0.0f) * light.intensity;

    vec3 reflectDir = reflect(-lightDir, norm);
//    float spec = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess)
    float spec = viewDir.x * 0.1;
    float distance = length(light.position - position);
    float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    vec3 diffuse = vec3(0.0f);
    vec3 specular = vec3(0.0f);
    vec3 ambient = vec3(0.15, 0.15, 0.15) * texture(textureMap, uvs).rgb;

    diffuse = light.color * diff * texture(textureMap, uvs).rgb;
    specular = light.color * spec;

    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;

    return (ambient + diffuse + specular);
}

vec3 CalcDirectionalLight(Light light, vec3 normal, vec3 position, vec3 viewDir) {
    return vec3(0.0);
}

vec3 CalcSpotLight(Light light, vec3 normal, vec3 position, vec3 viewDir) {
    float inner = light.innerCutoff;
    float outer = light.outerCutoff;

    return vec3(inner, outer, 0.0);
}

vec3 CalcAreaLight(Light light, vec3 normal, vec3 position, vec3 viewDir) {
    return vec3(0.0);
}

vec3 uncharted2Tonemap(const vec3 x)
{
    const float A = 0.15;
    const float B = 0.50;
    const float C = 0.10;
    const float D = 0.20;
    const float E = 0.02;
    const float F = 0.30;

    return ((x * (A * x + C * B) + D * E) / (x * (A * x + B) + D * F)) - E / F;
}

vec3 tonemapUncharted2(const vec3 color)
{
    const float W = 11.2;
    const float exposureBias = 2.0;
    vec3 curr = uncharted2Tonemap(exposureBias * color);
    vec3 whiteScale = 1.0 / uncharted2Tonemap(vec3(W));

    return curr * whiteScale;
}

void main() {
    vec3 norm = normalize(normal);
    vec3 viewDir = normalize(camPos - position);
    vec3 result = vec3(0.0f);

    for (int i = 0; i <= MAX_LIGHTS; i++) {
        Light light = lights[i];

        if (light.type == 0)
        result += CalcDirectionalLight(light, norm, position, viewDir);
        else if (light.type == 1)
        result += CalcPointLight(light, norm, position, viewDir);
        else if (light.type == 2)
        result += CalcAreaLight(light, norm, position, viewDir);
        else if (light.type == 3)
        result += CalcSpotLight(light, norm, position, viewDir);
    }

    FragColor = vec4(tonemapUncharted2(result), 1.0);
}